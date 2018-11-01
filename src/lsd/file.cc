#include "lsd/file.h"

#include <fstream>
#include <sstream>

std::string lsd::ReadText(const char* filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<std::string> lsd::ReadLines(const char* filename) {
  std::ifstream file(filename);
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(file, str)) {
      lines.push_back(str);
  }
  return lines;
}
