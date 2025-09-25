#include "InstructionFixture.h"

#include "instruction/LoadValueInstruction.h"


TEST_F(InstructionTest, LoadValue) {
  // Arrange
  vector<word> opcodes = { 0x6010, 0x6120, 0x6230, 0x6340, 0x6450 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<LoadValueInstruction>(opcodes);

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
