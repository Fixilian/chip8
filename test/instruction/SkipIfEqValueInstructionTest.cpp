#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfEqValueInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(SkipIfEqValueInstructionTest, Skip) {
  // Arrange
  vector<word> opcodes = { 0x3020, 0x3100, 0x3203, 0x3320, 0x3499 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x03, 0x01, 0x99 };
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<SkipIfEqValueInstruction>(opcodes);

  vector<const chip8::byte*> expected = {
    ctx->pc + kPcStep, ctx->pc + kPcStep, 
    ctx->pc + kPcStep * 2, ctx->pc + kPcStep * 2, 
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
