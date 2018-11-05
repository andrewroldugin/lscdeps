#include "lsd/processor.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "lsd/file.h"

lsd::File& lsd::Processor::ProcessFile(lsd::File& file) {
  std::string text = lsd::RemoveSingleLineComments(
                     lsd::RemoveMultiLineComments(
                     lsd::ReadText(file.path)));
  for (const auto& incl:lsd::ParseIncludes(text)) {
    auto f = std::make_unique<lsd::File>(SearchIncludePath(file.path, incl));
    ProcessFile(*f);
    file.files.push_back(std::move(f));
  }
  return file;
}

void lsd::Processor::PrintFile(const lsd::File& f, std::string indent) {
  std::cout << indent << f.path.filename() << std::endl;
  for (const auto& ff:f.files) {
    PrintFile(*ff, indent + tab_);
  }
 }

fs::path lsd::Processor::SearchIncludePath(const fs::path& path,
                                           const std::string& include) {
  // don't forget to check absolute path for include
  auto filename = GetFileName(include);
  if (fs::exists(filename)) {
    return fs::absolute(filename);
  } else {
    // log error
    // maybe replace with exception later
    std::cerr << "Failed at " << path
              << " => #include " << include
              << std::endl;
    return filename;
  }
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
