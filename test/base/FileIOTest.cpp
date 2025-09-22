#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "base/FileIO.h"
#include "exception/IOException.h"

namespace fs = std::filesystem;
using namespace std;
using namespace chip8;


class FileIOTest : public testing::Test {
 protected:
  string tmpFile = "test_tmp.bin";

  void TearDown() override {
    if (fs::exists(tmpFile)) {
      fs::remove(tmpFile);
    }
  }
};


TEST_F(FileIOTest, ReadFileSuccess) {
  // Arrange
  string data = "Hello, World!";
  {
    std::ofstream out(tmpFile, ios::binary);
    out.write(data.data(), data.size());
  }

  // Act
  string result = readFile(tmpFile, 1024);

  // Assert
  EXPECT_EQ(result, data);
}


TEST_F(FileIOTest, ReadFileTooLarge) {
  // Arrange
  string data = "ABC";
  {
    ofstream out(tmpFile, ios::binary);
    out.write(data.data(), data.size());
  }

  // Assert
  EXPECT_THROW(readFile(tmpFile, 2), IOException);
}


TEST_F(FileIOTest, ReadFileNotExists) {
  // Assert
  EXPECT_THROW(readFile("no_such_file.bin", 1024), IOException);
}


TEST_F(FileIOTest, WriteFileAndReadBack) {
  // Arrange
  string content = "Test123";

  // Act
  writeFile(tmpFile, content);

  // Assert
  ifstream in(tmpFile, ios::binary);
  string read((istreambuf_iterator<char>(in)), {});
  EXPECT_EQ(content, read);
}


TEST_F(FileIOTest, WriteFileToInvalidDir) {
  // Assert
  EXPECT_THROW(writeFile("/invalid_path/file.bin", "abc"), IOException);
}


TEST_F(FileIOTest, FromFileSuccess) {
  // Arrange
  vector<word> opcodes = { 0x1234, 0xABCD, 0xFFFF };
  {
    ofstream out(tmpFile, ios::binary);
    auto src = reinterpret_cast<const char*>(opcodes.data());
    out.write(src, opcodes.size() * sizeof(word));
  }

  // Act
  Rom rom = fromFile(tmpFile, 1024);

  // Assert
  EXPECT_EQ(rom.size(), opcodes.size() * sizeof(word));
  for (int i = 0; i < rom.size(); i++) {
    EXPECT_EQ(rom.opcodes()[i], opcodes[i]);
  }
}
