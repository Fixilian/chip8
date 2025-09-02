#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/ClearDisplayInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(ClearDisplayInstructionTest, ClearFrame) {
  // Arrange
  int w = 2;
  int h = 5;
  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContext(w * kBits, h, *mem, *keyboard);
  ClearDisplayInstruction cls_ins(0x00E0);
  
  vector<chip8::byte> input = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, 
    0xF0, 0x90, 0x90, 0x90, 0xF0
  };
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      ctx->frame.setByte(x, y, input[x + y * w]);
    }
  }

  // Act
  cls_ins.execute(*ctx);

  // Assert
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto b = ctx->frame.getByte(x, y);
      EXPECT_EQ(b, 0);
    }
  }
}
