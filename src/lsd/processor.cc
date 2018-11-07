#include "lsd/processor.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "lsd/file.h"
#include "lsd/include_error.h"

lsd::File& lsd::Processor::ProcessFile(lsd::File& file) {
  if (file.state == FileProcessState::PROCESSED) return file;

  file.state = FileProcessState::PROCESSING;

  std::string text = lsd::RemoveSingleLineComments(
                     lsd::RemoveMultiLineComments(
                     lsd::ReadText(file.path)));
  for (const auto& incl:lsd::ParseIncludes(text)) {
    try {
      File& f = GetFile(SearchIncludePath(file.path, incl));
      if (f.state == FileProcessState::PROCESSING)
        throw IncludeError("Cycle", file.path, incl);
      ProcessFile(f);
      file.files.push_back(&f);
    } catch (const IncludeError& e) {
      std::cerr << e.what() << std::endl;
    }
  }
  file.state = FileProcessState::PROCESSED;
  return file;
}

void lsd::Processor::PrintFile(const lsd::File& f, std::string indent) {
  std::cout << indent << f.path.filename().string() << std::endl;
  for (const auto* ff:f.files) {
    PrintFile(*ff, indent + tab_);
  }
 }

fs::path lsd::Processor::SearchIncludePath(const fs::path& path,
                                           const std::string& include) {
  auto filename = GetFileName(include);
  fs::path out;
  if (filename.is_absolute()) {
    if (fs::exists(filename)) out = filename;
  } else {
    if (lsd::IsParentInclude(include)) {
      auto incpath = path.parent_path();
      incpath /= filename;
      if (fs::exists(incpath)) out = incpath;
    }
    if (out.empty()) {
      for (auto incpath:include_dirs_) {
        incpath /= filename;
        if (fs::exists(incpath)) {
          out = incpath;
          break;
        }
      }
    }
  }
  if (out.empty()) throw IncludeError("Not found", path, include);
  return out;
}

void lsd::Processor::AddIncludeDir(const fs::path& dir) {
  include_dirs_.push_back(dir);
}

lsd::File& lsd::Processor::GetFile(const fs::path& path) {
  File* out;
  fs::path abs_path = fs::absolute(path);
  std::string abs_path_str = abs_path.string();
  auto iter = files_.find(abs_path_str);
  if (iter == files_.end()) {
    files_[abs_path_str] = std::make_unique<File>(abs_path);
    out = files_[abs_path_str].get();
  } else {
    out = iter->second.get();
  }
  return *out;
}

std::string lsd::ReadText(const fs::path& path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<std::string> lsd::ReadLines(const fs::path& path) {
  std::ifstream file(path);
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(file, str)) {
    lines.push_back(str);
  }
  return lines;
}

std::vector<std::string> lsd::ParseIncludes(const std::string& s) {
   std::smatch match;
   std::regex regex("#\\s*include\\s*([\"<]{1}[\\w\\s/.]+[\">]{1})");
   auto iter = s.begin();
   std::vector<std::string> out;
   while (std::regex_search(iter, s.end(), match, regex)) {
     out.push_back(match[1]);
     iter = match[0].second;
   }
   return out;
}

std::string lsd::RemoveMultiLineComments(const std::string& s) {
  std::regex re("/\\*[\\s\\S]*?\\*/");
  return std::regex_replace(s, re, "");
}

std::string lsd::RemoveSingleLineComments(const std::string& s) {
  std::regex re("//.*");
  return std::regex_replace(s, re, "");
}

fs::path lsd::GetFileName(const std::string& include) {
  return include.substr(1, include.size() - 2);
}

bool lsd::IsParentInclude(const std::string& include) {
  return include[0] != '<';
}
