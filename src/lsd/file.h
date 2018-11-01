#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const std::string&);
  std::vector<std::string> ReadLines(const std::string&);
  std::vector<std::string> ParseIncludes(const std::string& s);
}

#endif  // LSD_FILE_H
