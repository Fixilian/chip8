#include "InstructionFixture.h"

#include "instruction/LoadDtInstruction.h"


TEST_F(InstructionTest, LoadDt) {
  // Arrange
  vector<word> opcodes = { 0xF007, 0xF107, 0xF207, 0xF307, 0xF407 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<LoadDtInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ctx->setDt(expected[i]);
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
