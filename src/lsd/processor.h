#ifndef LSD_PROCESSOR_H
#define LSD_PROCESSOR_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const std::string&);
  std::vector<std::string> ReadLines(const std::string&);
  void ParseIncludes(const std::string&, std::vector<std::string>&);

  class File;
  class Processor;
}

class lsd::Processor {
  std::string tab_ = "  ";
  // temp storage for file includes
  std::vector<std::string> filenames_;
public:
  lsd::File& ProcessFile(lsd::File&);
  void PrintFile(const lsd::File&, std::string indent = "");
};

#endif  // LSD_PROCESSOR_H
