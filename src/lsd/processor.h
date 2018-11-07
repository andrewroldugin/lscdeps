#ifndef LSD_PROCESSOR_H
#define LSD_PROCESSOR_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace lsd {
  std::string ReadText(const fs::path&);
  std::vector<std::string> ReadLines(const fs::path&);
  std::vector<std::string> ParseIncludes(const std::string&);
  std::string RemoveMultiLineComments(const std::string&);
  std::string RemoveSingleLineComments(const std::string&);
  fs::path GetFileName(const std::string&);
  bool IsParentInclude(const std::string&);

  struct File;
  class Processor;
}

class lsd::Processor {
  std::string tab_ = "  ";
  std::vector<fs::path> include_dirs_;
private:
  fs::path SearchIncludePath(const fs::path&, const std::string&);
public:
  lsd::File& ProcessFile(lsd::File&);
  void PrintFile(const lsd::File&, std::string indent = "");
  void AddIncludeDir(const fs::path&);
};

#endif  // LSD_PROCESSOR_H
