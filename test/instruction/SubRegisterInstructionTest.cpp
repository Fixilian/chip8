#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/SubRegisterInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(SubRegisterInstructionTest, Sub) {
  // Arrange
  vector<word> opcodes = { 0x8015, 0x8125, 0x8235, 0x8345, 0x8455 };
  vector<chip8::byte> regs = { 0x80, 0x50, 0x40, 0x40, 0x20, 0x01};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<SubRegisterInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] - regs[i + 1]);
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


TEST(SubRegisterInstructionTest, Flag) {
  // Arrange
  vector<word> opcodes = { 0x8015, 0x8125, 0x8235, 0x8345, 0x8455 };
  vector<chip8::byte> regs = { 0xF0, 0xF1, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = { 0, 1, 0, 0, 1};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<SubRegisterInstruction>(opcodes);

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
