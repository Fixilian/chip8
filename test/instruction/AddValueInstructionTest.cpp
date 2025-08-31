#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/AddValueInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(AddValueInstructionTest, Add) {
  // Arrange
  vector<word> input = { 0x7010, 0x7120, 0x7230, 0x7340, 0x7450 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> expected = { 0x20, 0x40, 0x60, 0x80, 0xA0 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<chip8::byte> actual(input.size());
  vector<unique_ptr<AddValueInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<AddValueInstruction>(input[i]);
    ctx.registers[i] = regs[i];
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
