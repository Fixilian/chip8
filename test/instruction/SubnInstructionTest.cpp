#include "InstructionFixture.h"

#include "instruction/SubnInstruction.h"


TEST_F(InstructionTest, Subn) {
  // Arrange
  vector<word> opcodes = { 0x8017, 0x8127, 0x8237, 0x8347, 0x8457 };
  vector<chip8::byte> regs = { 0x01, 0x20, 0x40, 0x40, 0x50, 0x80};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SubnInstruction>(regs, opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i + 1] - regs[i]);
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


TEST_F(InstructionTest, SubnFlag) {
  // Arrange
  vector<word> opcodes = { 0x8017, 0x8127, 0x8237, 0x8347, 0x8457 };
  vector<chip8::byte> regs = { 0xF0, 0xF1, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = { 1, 0, 1, 1, 0};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SubnInstruction>(regs, opcodes);

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
