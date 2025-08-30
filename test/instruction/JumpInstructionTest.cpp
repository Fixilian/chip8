#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/JumpInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(JumpInstructionTest, Jump) {
  // Arrange
  vector<word> input = { 0x1600, 0x1700, 0x1800, 0x1900, 0x1999 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<const word*> expected(input.size());
  vector<const word*> actual(input.size());
  vector<unique_ptr<JumpInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = reinterpret_cast<const word*>(mem.mem() + mem_reserve);
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<JumpInstruction>(input[i]);
    word jmp = lowest12BitsOf(input[i]);
    expected[i] = reinterpret_cast<const word*>(mem.mem() + jmp);
  }

  // Act
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i]->execute(ctx);
    actual[i] = ctx.pc;
  }

  // Assert
  for (size_t i = 0; i < input.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
