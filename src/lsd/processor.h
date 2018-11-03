#ifndef LSD_PROCESSOR_H
#define LSD_PROCESSOR_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const std::string&);
  std::vector<std::string> ReadLines(const std::string&);
  std::vector<std::string> ParseIncludes(const std::string&);

  class File;
  class Processor;
}

class lsd::Processor {
  std::string tab_ = "  ";
public:
  lsd::File& ProcessFile(lsd::File&);
  void PrintFile(const lsd::File&, std::string indent = "");
};

#endif  // LSD_PROCESSOR_H
