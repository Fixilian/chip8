#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "emulator/Cli.h"

using namespace std;
using namespace chip8;


class CliTest : public testing::Test {
 public:
  char** convert_argv(vector<string> vargv) {
    argc = static_cast<int>(vargv.size());
    argv = new char*[argc];
    for (int i = 0; i < argc; i += 1) {
      auto len = vargv[i].length();
      argv[i] = new char[len + 1];
      strcpy(argv[i], vargv[i].c_str());
    }
    return argv;
  }

 protected:
  char** argv = nullptr;
  int argc = 0;

  void TearDown() override {
    if (!argv) {
      return;
    }
    for (int i = 0; i < argc; i += 1) {
      delete[] argv[i];
    }
    delete[] argv;
  }
};


TEST_F(CliTest, Positional) {
  // Arrange
  vector<string> vargv = {"./app", "rom.ch8"};
  int argc = static_cast<int>(vargv.size());
  int err = 0;

  // Act
  auto args = parse(argc, convert_argv(vargv), err);

  // Assert
  EXPECT_EQ(err, 0);
  EXPECT_EQ(args.getRomFile(), vargv[1]);
  EXPECT_TRUE(args.isBinaryRom());
}


TEST_F(CliTest, TextRom) {
  // Arrange
  vector<string> vargv = {"./app", "rom.txt", "-t"};
  int argc = static_cast<int>(vargv.size());
  int err = 0;

  // Act
  auto args = parse(argc, convert_argv(vargv), err);

  // Assert
  EXPECT_EQ(err, 0);
  EXPECT_EQ(args.getRomFile(), vargv[1]);
  EXPECT_FALSE(args.isBinaryRom());
}


TEST_F(CliTest, RomRequired) {
  // Arrange
  vector<string> vargv = {"./app"};
  int argc = static_cast<int>(vargv.size());
  int err = 0;

  // Act
  auto args = parse(argc, convert_argv(vargv), err);

  // Assert
  EXPECT_NE(err, 0);
}


TEST_F(CliTest, CfgFile) {
  // Arrange
  vector<string> vargv = {"./app", "rom.ch8", "-c", "cfg.cfg"};
  int argc = static_cast<int>(vargv.size());
  int err = 0;

  // Act
  auto args = parse(argc, convert_argv(vargv), err);

  // Assert
  EXPECT_EQ(err, 0);
  EXPECT_EQ(args.getCfgFile(), vargv[3]);
}


TEST_F(CliTest, Specification) {
  // Arrange
  vector<string> vargv = {"./app", "rom.ch8", "--mem_size=8192", 
    "--stack_size=32", "--display_width=128", "--display_height=64"};
  int argc = static_cast<int>(vargv.size());
  int err = 0;
  int memory_size = 8192;
  int stack_size = 32;
  int display_width = 128;
  int display_height = 64;

  // Act
  auto args = parse(argc, convert_argv(vargv), err);

  // Assert
  auto spec = args.getSpecification();
  EXPECT_EQ(err, 0);
  EXPECT_EQ(spec.getMemorySize(), memory_size);
  EXPECT_EQ(spec.getStackSize(), stack_size);
  EXPECT_EQ(spec.getDisplayWidth(), display_width);
  EXPECT_EQ(spec.getDisplayHeight(), display_height);
}
