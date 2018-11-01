#include "lsd/file.h"

#include <fstream>
#include <sstream>

std::string lsd::ReadText(const char* filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}
