#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfPressedInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(SkipIfPressedInstructionTest, Skip) {
  // Arrange
  vector<word> opcodes = { 0xE09E, 0xE19E, 0xE29E, 0xE39E, 0xE49E };
  vector<chip8::byte> regs = { 0x00, 0x01, 0x02, 0x03, 0x04 };
  vector<bool> pressed = {1, 0, 0, 1, 1};
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor(pressed);
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<SkipIfPressedInstruction>(opcodes);

  vector<const chip8::byte*> expected = {
    ctx->pc + kPcStep, ctx->pc + kPcStep, 
    ctx->pc + kPcStep, ctx->pc + kPcStep * 2, 
    ctx->pc + kPcStep * 3
  };

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
