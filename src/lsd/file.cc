#include "lsd/file.h"

#include <fstream>
#include <regex>
#include <sstream>

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

std::vector<std::string> lsd::ParseIncludes(const std::string& s) {
   std::smatch match;
   std::regex regex("#\\s*include\\s*([\"<]{1}[\\w\\s/.]+[\">]{1})");
   std::vector<std::string> includes;
   auto iter = s.begin();
   while (std::regex_search(iter, s.end(), match, regex)) {
     includes.push_back(match[1]);
     iter = match[0].second;
   }
   return includes;
}
