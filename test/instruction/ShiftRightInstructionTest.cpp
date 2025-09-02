#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/ShiftRightInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(ShiftRightInstructionTest, Shift) {
  // Arrange
  vector<word> opcodes = { 0x8016, 0x8126, 0x8236, 0x8346, 0x8456 };
  vector<chip8::byte> regs = { 0x80, 0x50, 0x40, 0x40, 0x20, 0x01};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<ShiftRightInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] >> 1);
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


TEST(ShiftRightInstructionTest, Flag) {
  // Arrange
  vector<word> opcodes = { 0x8015, 0x8125, 0x8235, 0x8345, 0x8455 };
  vector<chip8::byte> regs = { 0xF0, 0xF1, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = { 0, 1, 1, 0, 0};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  auto ins = generateInstructions<ShiftRightInstruction>(opcodes);

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
