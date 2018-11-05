#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace lsd {
  struct File;
}

struct lsd::File {
  fs::path path;
  std::vector<std::unique_ptr<lsd::File>> files;
  File(const fs::path&);
};

#endif  // LSD_FILE_H
