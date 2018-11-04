#include "lsd/file.h"
#include "lsd/processor.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    lsd::Processor p;
    lsd::File f(argv[1]);
    p.PrintFile(p.ProcessFile(f));
  }
  return 0;
}
