#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadRegisterInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(LoadRegisterInstructionTest, Load) {
  // Arrange
  vector<word> opcodes = { 0x8050, 0x8160, 0x8270, 0x8380, 0x8490 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0};
  vector<chip8::byte> expected = { 0x60, 0x70, 0x80, 0x90, 0xA0 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<LoadRegisterInstruction>(opcodes);

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
