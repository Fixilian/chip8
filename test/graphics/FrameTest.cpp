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


TEST(FrameTest, Draw) {
  // Arrange
  chip8::byte sprite[] = { 0xF0, 0x90, 0x90, 0x90, 0xF0 };
  int sw = kBits;
  int sh = 5;
  int w = 2 * kBits;
  int h = 10;
  int x0 = 3;
  int y0 = 3;
  Frame f(w, h);

  // Act
  f.draw(sprite, sh, x0, y0);

  // Assert
  for (int y = 0; y < sh; y += 1) {
    chip8::byte sb = sprite[y];
    for (int x = 0; x < sw; x += 1) {
      chip8::byte spixel = getBit(sb, x);
      chip8::byte fpixel = f.getPixel(x + x0, y + y0);
      EXPECT_EQ(fpixel, spixel);
    }
  }
}


TEST(FrameTest, Clear) {
  // Arrange
  vector<chip8::byte> input = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, 
    0xF0, 0x90, 0x90, 0x90, 0xF0
  };
  int w = 2;
  int h = 5;
  Frame f(w * kBits, h);
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      f.setByte(x, y, input[x + y * w]);
    }
  }

  // Act
  f.clear();

  // Assert
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto b = f.getByte(x, y);
      EXPECT_EQ(b, 0);
    }
  }
}


TEST(FrameTest, Copy) {
  // Arrange
  vector<chip8::byte> input = { 0xF0, 0x90, 0x90, 0x90, 0xF0};
  int w = 1;
  int h = 5;
  int pw = w * kBits;
  Frame f(pw, h);
  Frame f2(pw, h);
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      f.setByte(x, y, input[x + y * w]);
    }
  }

  // Act
  f2.copy(f);

  // Assert
  for (int x = 0; x < pw; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto p = f.getPixel(x, y);
      auto p2 = f2.getPixel(x, y);
      EXPECT_EQ(p, p2);
    }
  }
}
