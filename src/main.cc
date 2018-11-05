#include <filesystem>

#include "lsd/file.h"
#include "lsd/processor.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc > 1) {
    lsd::Processor p;
    lsd::File f(fs::absolute(argv[1]));
    p.PrintFile(p.ProcessFile(f));
  }
  return 0;
}
