#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadValueInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(LoadValueInstructionTest, Load) {
  // Arrange
  vector<word> input = { 0x6010, 0x6120, 0x6230, 0x6340, 0x6450 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<chip8::byte> actual(input.size());
  vector<unique_ptr<LoadValueInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<LoadValueInstruction>(input[i]);
  }

  // Act
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i]->execute(ctx);
    actual[i] = ctx.registers[i];
  }

  // Assert
  for (size_t i = 0; i < input.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
