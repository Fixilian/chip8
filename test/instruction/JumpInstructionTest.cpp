#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/JumpInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(JumpInstructionTest, Jump) {
  // Arrange
  vector<word> opcodes = { 0x1600, 0x1700, 0x1800, 0x1900, 0x1999 };
  vector<const chip8::byte*> expected(opcodes.size());
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();

  auto mem = generateMemory();
  auto ctx = generateContext(*mem);
  auto ins = generateInstructions<JumpInstruction>(opcodes);
  
  for (size_t i = 0; i < n; i += 1) {
    word jmp = lowest12BitsOf(opcodes[i]);
    expected[i] = mem->mem() + jmp;
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
