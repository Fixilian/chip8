#include "InstructionFixture.h"

#include "instruction/BitwiseOrInstruction.h"


TEST_F(InstructionTest, BitwiseOr) {
  // Arrange
  vector<word> opcodes = { 0x8011, 0x8121, 0x8231, 0x8341, 0x8451 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<BitwiseOrInstruction>(regs, opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] | regs[i + 1]);
  }

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
