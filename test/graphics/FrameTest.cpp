#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "graphics/Frame.h"

using namespace std;
using namespace chip8;


TEST(FrameTest, GetSetByte) {
  // Arrange
  vector<chip8::byte> expected = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, 
    0xF0, 0x90, 0x90, 0x90, 0xF0
  };
  int w = 2;
  int h = 5;
  Frame f(w * kBits, h);

  // Act
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      f.setByte(x, y, expected[x + y * w]);
    }
  }

  // Assert
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto b = f.getByte(x, y);
      EXPECT_EQ(b, expected[x + y * w]);
    }
  }
}


TEST(FrameTest, SetByteGetPixel) {
  // Arrange
  vector<chip8::byte> input = { 0xF0, 0x90, 0x90, 0x90, 0xF0};
  vector<chip8::byte> expected = {
    1, 1, 1, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0, 0,
  };
  int w = 1;
  int h = 5;
  int pw = w * kBits;
  Frame f(pw, h);

  // Act
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      f.setByte(x, y, input[x + y * w]);
    }
  }

  // Assert
  for (int x = 0; x < pw; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto p = f.getPixel(x, y);
      EXPECT_EQ(p, expected[x + y * pw]);
    }
  }
}


TEST(FrameTest, GetSetPixel) {
  // Arrange
  vector<chip8::byte> expected = {
    1, 1, 1, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0, 0,
  };
  int w = 1;
  int h = 5;
  int pw = w * kBits;
  Frame f(pw, h);

  // Act
  for (int x = 0; x < pw; x += 1) {
    for (int y = 0; y < h; y += 1) {
      f.setPixel(x, y, expected[x + y * pw]);
    }
  }

  // Assert
  for (int x = 0; x < pw; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto p = f.getPixel(x, y);
      EXPECT_EQ(p, expected[x + y * pw]);
    }
  }
}
