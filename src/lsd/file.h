#ifndef LSD_FILE_H
#define LSD_FILE_H

#include <memory>
#include <string>
#include <vector>

namespace lsd {
  class File;
}

struct lsd::File {
  std::string path;
  std::vector<std::unique_ptr<lsd::File>> includes;
  File(const std::string&);
};

#endif  // LSD_FILE_H
