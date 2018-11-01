#include <gtest/gtest.h>

#include "lsd/file.h"

namespace lsd {
TEST(ReadTextTest, ReadFileToString) {
  std::string expected = "one\ntwo\nthree\n";
  EXPECT_EQ(expected, ReadText("data/read_text/file.txt"));
}
}
