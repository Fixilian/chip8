#include "InstructionFixture.h"

#include "instruction/LoadRegisterInstruction.h"


TEST_F(InstructionTest, LoadRegister) {
  // Arrange
  vector<word> opcodes = { 0x8050, 0x8160, 0x8270, 0x8380, 0x8490 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0};
  vector<chip8::byte> expected = { 0x60, 0x70, 0x80, 0x90, 0xA0 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<LoadRegisterInstruction>(regs, opcodes);

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
