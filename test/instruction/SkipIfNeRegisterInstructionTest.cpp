#include "InstructionFixture.h"

#include "instruction/SkipIfNeRegisterInstruction.h"


TEST_F(InstructionTest, SkipIfNeRegister) {
  // Arrange
  vector<word> opcodes = { 0x9010, 0x9130, 0x9210, 0x9240, 0x9340 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x99, 0x01, 0x99 };
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SkipIfNeRegisterInstruction>(regs, opcodes);
  
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
