#ifndef LSD_PROCESSOR_H
#define LSD_PROCESSOR_H

#include <string>
#include <vector>

namespace lsd {
  std::string ReadText(const std::string&);
  std::vector<std::string> ReadLines(const std::string&);
  void ParseIncludes(const std::string&, std::vector<std::string>&);
  std::string RemoveMultiLineComments(std::string);
  std::string RemoveSingleLineComments(std::string);  

  class File;
  class Processor;
}

class lsd::Processor {
  std::string tab_ = "  ";
  // temp storage for file includes
  std::vector<std::string> includes_;
public:
  lsd::File& ProcessFile(lsd::File&);
  void PrintFile(const lsd::File&, std::string indent = "");
};

#endif  // LSD_PROCESSOR_H
