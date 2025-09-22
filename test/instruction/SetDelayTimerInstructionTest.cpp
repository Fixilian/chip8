#include "InstructionFixture.h"

#include "instruction/SetDelayTimerInstruction.h"


TEST_F(InstructionTest, SetDelayTimer) {
  // Arrange
  vector<word> opcodes = { 0xF015, 0xF115, 0xF215, 0xF315, 0xF415 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SetDelayTimerInstruction>(regs, opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->dt();
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
