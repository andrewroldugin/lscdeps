#ifndef LSD_INCLUDE_ERROR_H
#define LSD_INCLUDE_ERROR_H

#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

namespace lsd {
  class IncludeError;
}

class lsd::IncludeError: public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
  IncludeError(const std::string&, const fs::path&, const std::string&);
};

#endif  // LSD_INCLUDE_ERROR_H
