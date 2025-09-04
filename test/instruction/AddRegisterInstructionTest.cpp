#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/AddRegisterInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(AddRegisterInstructionTest, Add) {
  // Arrange
  vector<word> opcodes = { 0x8014, 0x8124, 0x8234, 0x8344, 0x8454 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<AddRegisterInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] + regs[i + 1]);
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


TEST(AddRegisterInstructionTest, Flag) {
  // Arrange
  vector<word> opcodes = { 0x8014, 0x8124, 0x8234, 0x8344, 0x8454 };
  vector<chip8::byte> regs = { 0xF0, 0xF0, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = { 1, 0, 0, 1, 1};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<AddRegisterInstruction>(opcodes);

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
