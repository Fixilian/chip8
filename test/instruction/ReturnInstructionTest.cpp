#include <gtest/gtest.h>

#include <vector>

#include "instruction/ReturnInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(ReturnInstructionTest, Return) {
  // Arrange
  vector<word> input = { 600, 700, 800, 900, 1000 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<const word*> expected(input.size());
  vector<const word*> actual(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = reinterpret_cast<const word*>(mem.mem() + mem_reserve);
  for (size_t i = 0; i < input.size(); i += 1) {
    ctx.stack.push(input[i]);
    expected[i] = reinterpret_cast<const word*>(mem.mem() + input[i]);
  }
  ReturnInstruction ret_ins(0x00EE);

  // Act
  for (size_t i = 0; i < input.size(); i += 1) {
    ret_ins.execute(ctx);
    actual[i] = ctx.pc;
  }

  // Assert
  for (size_t i = 0; i < input.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[input.size() - 1 - i]);
  }
}
