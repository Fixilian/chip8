#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/BitwiseAndInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(BitwiseAndInstructionTest, BitwiseAnd) {
  // Arrange
  vector<word> opcodes = { 0x8012, 0x8122, 0x8232, 0x8342, 0x8452 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  vector<chip8::byte> expected(opcodes.size());
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<BitwiseAndInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    expected[i] = static_cast<chip8::byte>(regs[i] & regs[i + 1]);
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
