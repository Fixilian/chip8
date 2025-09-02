#include <gtest/gtest.h>

#include <vector>

#include "instruction/ReturnInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(ReturnInstructionTest, Return) {
  // Arrange
  vector<word> input = { 600, 700, 800, 900, 1000 };
  vector<const chip8::byte*> expected(input.size());
  vector<const chip8::byte*> actual(input.size());
  size_t n = input.size();

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory();
  auto ctx = generateContext(*mem, *keyboard);
  ReturnInstruction ret_ins(0x00EE);

  for (size_t i = 0; i < n; i += 1) {
    ctx->stack.push(input[i]);
    expected[i] = mem->mem() + input[i];
  }

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ret_ins.execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[n - 1 - i]);
  }
}
