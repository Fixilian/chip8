#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/AddValueInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(AddValueInstructionTest, Add) {
  // Arrange
  vector<word> opcodes = { 0x7010, 0x7120, 0x7230, 0x7340, 0x7450 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> expected = { 0x20, 0x40, 0x60, 0x80, 0xA0 };
  vector<chip8::byte> actual(opcodes.size());

  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem);
  auto ins = generateInstructions<AddValueInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < ins.size(); i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
