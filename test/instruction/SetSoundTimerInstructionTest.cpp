#include "InstructionFixture.h"

#include "instruction/SetSoundTimerInstruction.h"


TEST_F(InstructionTest, SetSoundTimer) {
  // Arrange
  vector<word> opcodes = { 0xF018, 0xF118, 0xF218, 0xF318, 0xF418 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<SetSoundTimerInstruction>(regs, opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->st();
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
