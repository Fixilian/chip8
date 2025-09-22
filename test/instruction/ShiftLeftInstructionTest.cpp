#include "InstructionFixture.h"

#include "instruction/ShiftLeftInstruction.h"


TEST_F(InstructionTest, ShiftLeft) {
  // Arrange
  vector<word> opcodes = { 0x801E, 0x812E, 0x823E, 0x834E, 0x845E };
  vector<chip8::byte> regs = { 0x60, 0x50, 0x40, 0x40, 0x20, 0x01};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<ShiftLeftInstruction>(regs, opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] << 1);
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


TEST_F(InstructionTest, ShiftLeftFlag) {
  // Arrange
  vector<word> opcodes = { 0x801E, 0x812E, 0x823E, 0x834E, 0x845E };
  vector<chip8::byte> regs = { 0xF0, 0xF1, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = { 1, 1, 0, 0, 1};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<ShiftLeftInstruction>(regs, opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[kFlagRegister];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
