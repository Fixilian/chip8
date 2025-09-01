#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/JumpWithOffsetInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(JumpWithOffsetInstructionTest, Jump) {
  // Arrange
  vector<word> opcodes = { 0xB600, 0xB700, 0xB800, 0xB900, 0xB999 };
  vector<chip8::byte> regs = { 0x01, 0xF0, 0x01, 0x40, 0xD0, 0x60};
  vector<const chip8::byte*> expected(opcodes.size());
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem);
  auto ins = generateInstructions<JumpWithOffsetInstruction>(opcodes);
  
  for (size_t i = 0; i < n; i += 1) {
    word jmp = lowest12BitsOf(opcodes[i]);
    expected[i] = mem->mem() + jmp + regs[0];
  }

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
