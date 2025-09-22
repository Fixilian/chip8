#include "InstructionFixture.h"

#include "instruction/BitwiseAndInstruction.h"


TEST_F(InstructionTest, BitwiseAnd) {
  // Arrange
  vector<word> opcodes = { 0x8012, 0x8122, 0x8232, 0x8342, 0x8452 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<BitwiseAndInstruction>(regs, opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] & regs[i + 1]);
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
