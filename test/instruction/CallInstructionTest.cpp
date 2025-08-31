#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/CallInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(CallInstructionTest, Call) {
  // Arrange
  vector<word> input = { 0x2600, 0x2700, 0x2800, 0x2900, 0x2999 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<const word*> expected(input.size());
  vector<word> expected_stack(input.size());
  vector<const word*> actual(input.size());
  vector<unique_ptr<CallInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = reinterpret_cast<const word*>(mem.mem() + mem_reserve);
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<CallInstruction>(input[i]);
    word jmp = lowest12BitsOf(input[i]);
    expected[i] = reinterpret_cast<const word*>(mem.mem() + jmp);
  }
  for (size_t i = 0; i < input.size() - 1; i += 1) {
    expected_stack[input.size() - 2 - i] = lowest12BitsOf(input[i]);
  }
  expected_stack[input.size() - 1] = static_cast<word>(mem_reserve);

  // Act
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i]->execute(ctx);
    actual[i] = ctx.pc;
  }

  // Assert
  for (size_t i = 0; i < input.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
  for (size_t i = 0; i < input.size(); i += 1) {
    word stack_top = ctx.stack.pop();
    EXPECT_EQ(stack_top, expected_stack[i]);
  }
}
