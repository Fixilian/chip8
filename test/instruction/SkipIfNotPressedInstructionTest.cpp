#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfNotPressedInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(SkipIfNotPressedInstructionTest, Skip) {
  // Arrange
  vector<word> opcodes = { 0xE0A1, 0xE1A1, 0xE2A1, 0xE3A1, 0xE4A1 };
  vector<chip8::byte> regs = { 0x00, 0x01, 0x02, 0x03, 0x04 };
  vector<bool> pressed = {1, 0, 0, 1, 1};
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor(pressed);
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<SkipIfNotPressedInstruction>(opcodes);

  vector<const chip8::byte*> expected = {
    ctx->pc, ctx->pc + kPcStep, 
    ctx->pc + kPcStep * 2, ctx->pc + kPcStep * 2, 
    ctx->pc + kPcStep * 2
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
