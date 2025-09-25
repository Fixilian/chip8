#include "InstructionFixture.h"

#include "instruction/SkipIfNeValueInstruction.h"


TEST_F(InstructionTest, SkipIfNeValue) {
  // Arrange
  vector<word> opcodes = { 0x4020, 0x4100, 0x4203, 0x4320, 0x4499 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x03, 0x01, 0x99 };
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SkipIfNeValueInstruction>(regs, opcodes);

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
