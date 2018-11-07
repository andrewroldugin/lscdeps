#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace lsd {
  struct File;
  enum class FileProcessState;
}

enum class lsd::FileProcessState {
  STANDBY,
  PROCESSING,
  PROCESSED
};

struct lsd::File {
  FileProcessState state = FileProcessState::STANDBY;
  fs::path path;
  std::vector<File*> files;
  File(const fs::path&);
};

#endif  // LSD_FILE_H
