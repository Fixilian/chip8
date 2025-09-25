#include "InstructionFixture.h"

#include "instruction/BitwiseXorInstruction.h"


TEST_F(InstructionTest, BitwiseXor) {
  // Arrange
  vector<word> opcodes = { 0x8013, 0x8123, 0x8233, 0x8343, 0x8453 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<BitwiseXorInstruction>(regs, opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] ^ regs[i + 1]);
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
