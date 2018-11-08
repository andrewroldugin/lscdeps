#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <filesystem>
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
  int counter = 0;
  FileProcessState state = FileProcessState::STANDBY;
  fs::path path;
  std::vector<const File*> files;
  File(const fs::path&);
};

#endif  // LSD_FILE_H
