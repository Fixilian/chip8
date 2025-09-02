#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SetSoundTimerInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(SetSoundTimerInstructionTest, Set) {
  // Arrange
  vector<word> opcodes = { 0xF018, 0xF118, 0xF218, 0xF318, 0xF418 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<SetSoundTimerInstruction>(opcodes);

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
