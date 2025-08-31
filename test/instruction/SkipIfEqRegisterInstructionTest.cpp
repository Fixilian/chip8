#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfEqRegisterInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(SkipIfEqRegisterInstructionTest, Skip) {
  // Arrange
  vector<word> opcodes = { 0x5010, 0x5130, 0x5210, 0x5240, 0x5340 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x99, 0x01, 0x99 };
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem);
  auto ins = generateInstructions<SkipIfEqRegisterInstruction>(opcodes);
  
  vector<const chip8::byte*> expected = {
    ctx->pc, ctx->pc + kPcStep, 
    ctx->pc + kPcStep, ctx->pc + kPcStep * 2, 
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
