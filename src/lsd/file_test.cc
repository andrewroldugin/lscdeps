#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lsd/file.h"

using namespace lsd;

TEST(ReadTextTest, ReadFileToString) {
  std::string expected = "one\ntwo\nthree\n";
  EXPECT_EQ(expected, ReadText("data/read_text/file.txt"));
}

TEST(ReadTextTest, ReadFileLines) {
  auto actual = ReadLines("data/read_text/file.txt");
  std::vector<std::string> expected = {"one", "two", "three"};
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}

TEST(ProcessorTest, ParseIncludes) {
  std::string file = "data/file_includes/file";
  auto expected = ReadLines(file + ".inc");
  auto actual = ParseIncludes(ReadText(file + ".h"));
  EXPECT_THAT(actual, ::testing::ContainerEq(expected));
}
