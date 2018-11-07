#include <filesystem>

#include "tclap/CmdLine.h"

#include "lsd/file.h"
#include "lsd/processor.h"

namespace fs = std::filesystem;

using namespace TCLAP;

class LsdOutput: public StdOutput {
public:
  virtual void failure(CmdLineInterface&, ArgException& e) {
    std::cerr << "Something went wrong: " << std::endl
              << e.what() << std::endl;
    exit(1);
  }

  virtual void usage(CmdLineInterface& c) {
    std::cout << "Usage: " << fs::path(c.getProgramName()).filename().string()
              << " <OPTION> ... <FILE> ..."
              << std::endl
              << c.getMessage() << " in the FILEs"
              << " (the current directory by default)"
              << std::endl << std::endl;
    std::list<Arg*> args = c.getArgList();
    for (ArgListIterator it = args.begin(); it != args.end(); it++)
      std::cout << "  " << (*it)->longID()
                << "  (" << (*it)->getDescription() << ")" << std::endl;
  }

  virtual void version(CmdLineInterface& c) {
    std::cout << fs::path(c.getProgramName()).filename().string()
              << " " << c.getVersion() << std::endl
              << std::endl
              << c.getMessage() << std::endl << std::endl
              << "Written by Andrew Roldugin" << std::endl;
  }
};

int main(int argc, char* argv[]) {
  try {
    CmdLine cmd("List dependencies for C/C++ code", ' ', "0.1");
    LsdOutput output;
    cmd.setOutput(&output);

    MultiArg<std::string> dirsarg("I", "include", "add include directory",
                                  false, "DIR");
    cmd.add(dirsarg);
    UnlabeledMultiArg<std::string> filesarg("files", "file to process",
                                            false, "FILE");
    cmd.add(filesarg);
    cmd.parse(argc, argv);

    lsd::Processor p;

    for (const auto& arg:dirsarg.getValue()) {
      p.AddIncludeDir(arg);
    }

    auto files = filesarg.getValue();
    if (files.size()) {
      for (const auto& arg:files) {
        p.PrintFile(arg);
      }
    } else {
      p.PrintFile(fs::current_path());
    }
    p.PrintStat();
  } catch (ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId()
              << std::endl;
  }
  return 0;
}
