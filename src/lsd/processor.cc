#include "lsd/processor.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "lsd/file.h"

lsd::File& lsd::Processor::ProcessFile(lsd::File& file) {
  lsd::ParseIncludes(lsd::ReadText(file.path), includes_);
  for (const auto& incl:includes_) {
    file.files.push_back(std::make_unique<lsd::File>(incl));
  }
  includes_.clear();
  return file;
}

void lsd::Processor::PrintFile(const lsd::File& f, std::string indent) {
  std::cout << indent << f.path << std::endl;
  for (const auto& ff:f.files) {
    PrintFile(*ff, indent + tab_);
  }
 }

std::string lsd::ReadText(const std::string& filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<std::string> lsd::ReadLines(const std::string& filename) {
  std::ifstream file(filename);
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(file, str)) {
    lines.push_back(str);
  }
  return lines;
}

void lsd::ParseIncludes(const std::string& s, std::vector<std::string>& out) {
   std::smatch match;
   std::regex regex("#\\s*include\\s*([\"<]{1}[\\w\\s/.]+[\">]{1})");
   std::vector<std::string> includes;
   auto iter = s.begin();
   while (std::regex_search(iter, s.end(), match, regex)) {
     out.push_back(match[1]);
     iter = match[0].second;
   }
}
