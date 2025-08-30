#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/ClearDisplayInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(ClearDisplayInstructionTest, ClearFrame) {
  // Arrange
  vector<chip8::byte> input = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, 
    0xF0, 0x90, 0x90, 0x90, 0xF0
  };
  int w = 2;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w * kBits, h);
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      ctx.frame.setByte(x, y, input[x + y * w]);
    }
  }
  ClearDisplayInstruction cls_ins(0x00E0);

  // Act
  cls_ins.execute(ctx);

  // Assert
  for (int x = 0; x < w; x += 1) {
    for (int y = 0; y < h; y += 1) {
      auto b = ctx.frame.getByte(x, y);
      EXPECT_EQ(b, 0);
    }
  }
}
