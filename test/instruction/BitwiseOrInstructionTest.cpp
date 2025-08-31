#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/BitwiseOrInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(BitwiseOrInstructionTest, BitwiseOr) {
  // Arrange
  vector<word> input = { 0x8011, 0x8121, 0x8231, 0x8341, 0x8451 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0};
  vector<chip8::byte> expected(input.size());
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<chip8::byte> actual(input.size());
  vector<unique_ptr<BitwiseOrInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<BitwiseOrInstruction>(input[i]);
    expected[i] = static_cast<chip8::byte>(regs[i] | regs[i + 1]);
  }
  for (size_t i = 0; i < regs.size(); i += 1) {
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
