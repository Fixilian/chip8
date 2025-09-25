#include "InstructionFixture.h"

#include "instruction/SkipIfEqValueInstruction.h"


TEST_F(InstructionTest, SkipIfEqValue) {
  // Arrange
  vector<word> opcodes = { 0x3020, 0x3100, 0x3203, 0x3320, 0x3499 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x03, 0x01, 0x99 };
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SkipIfEqValueInstruction>(regs, opcodes);

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
