#ifndef LSD_PROCESSOR_H
#define LSD_PROCESSOR_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const std::string&);
  std::vector<std::string> ReadLines(const std::string&);
  std::vector<std::string> ParseIncludes(const std::string&);
}

#endif  // LSD_PROCESSOR_H
