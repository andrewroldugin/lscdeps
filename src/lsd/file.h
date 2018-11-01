#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const char*);
  std::vector<std::string> ReadLines(const char*);
}

#endif  // LSD_FILE_H
