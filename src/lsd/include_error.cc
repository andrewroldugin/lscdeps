#include "lsd/include_error.h"

lsd::IncludeError::IncludeError(const std::string& text, const fs::path& path,
                                const std::string& include):
  IncludeError(text + " in " + path.string() + " => #include " + include) {
}
