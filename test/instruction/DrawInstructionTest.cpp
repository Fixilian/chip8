#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/DrawInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(DrawInstructionTest, Draw) {
  // Arrange
  int spriteNumber = 1;
  int w = 2 * kBits;
  int h = 10;
  int sw = kBits;
  int sh = 5;
  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContext(w, h, *mem, *keyboard);
  DrawInstruction draw_ins(0xD015);
  auto sprite = mem->getDigitSprite(spriteNumber);
  chip8::byte x0 = 3;
  chip8::byte y0 = 3;
  ctx->registers[0] = x0;
  ctx->registers[1] = y0;
  ctx->i = static_cast<word>(sprite - mem->mem());

  // Act
  draw_ins.execute(*ctx);

  // Assert
  for (int y = 0; y < sh; y += 1) {
    chip8::byte sb = sprite[y];
    for (int x = 0; x < sw; x += 1) {
      chip8::byte spixel = getBit(sb, x);
      chip8::byte fpixel = ctx->frame.getPixel(x + x0, y + y0);
      EXPECT_EQ(fpixel, spixel);
    }
  }
}
