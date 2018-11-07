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

  std::string text = RemoveSingleLineComments(
					      RemoveMultiLineComments(
								      ReadText(file.path)));
  for (const auto& incl:ParseIncludes(text)) {
    try {
      File& f = GetFile(SearchIncludePath(file.path, incl));
      if (f.state == FileProcessState::PROCESSING)
        throw IncludeError("Cycle", file.path, incl);
      ++f.counter;
      file.files.push_back(&ProcessFile(f));
    } catch (const IncludeError& e) {
      std::cerr << e.what() << std::endl;
    }
  }
  file.state = FileProcessState::PROCESSED;
  return file;
}

void lsd::Processor::PrintFile(const lsd::File& f, const std::string& indent) {
  std::cout << indent << f.path.filename().string() << std::endl;
  for (auto ff:f.files) {
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
    auto f = std::make_unique<File>(abs_path);
    out = f.get();
    files_[abs_path_str] = std::move(f);
  } else {
    out = iter->second.get();
  }
  return *out;
}

void lsd::Processor::PrintFile(const fs::path& path) {
  if (!fs::exists(path)) {
    std::cerr << "Cannot access " << path << ": No such file or directory"
              << std::endl;
    return;
  }
  if (fs::is_directory(path)) {
    std::regex re(".*\\.(h|hpp|hxx|c|cc|cpp|cxx)$",
                  std::regex_constants::icase);
    for (fs::recursive_directory_iterator it(path), end; it != end; ++it) {
      std::string name = it->path().filename().string();
      if (std::regex_match(name, re)) {
        PrintFile(ProcessFile(GetFile(it->path())));
      }
    }
  } else {
    PrintFile(ProcessFile(GetFile(path)));
  }
}

void lsd::Processor::PrintStat() const {
  std::vector<const File*> v;
  int size = std::count_if(files_.cbegin(), files_.cend(),
                           [](const auto& p){return p.second->counter > 1;});
  v.reserve(size);
  // How to make filtermap?
  // use imperative way instead
  for (const auto& p:files_) {
    if (p.second->counter > 1) {
      v.push_back(p.second.get());
    }
  }
  std::sort(v.begin(), v.end(),
	    [](auto a, auto b) -> bool{return a->counter > b->counter;});
  for_each(v.begin(), v.end(),
	   [](auto f){
	     std::cout << f->path.filename().string() << " - " << f->counter
		       << std::endl;
	   });
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
