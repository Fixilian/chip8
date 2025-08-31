#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfEqValueInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(SkipIfEqValueInstructionTest, Skip) {
  // Arrange
  vector<word> input = { 0x3620, 0x3700, 0x3803, 0x3920, 0x3299 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x03, 0x01, 0x99 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<const chip8::byte*> actual(input.size());
  vector<unique_ptr<SkipIfEqValueInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  ctx.registers[6] = regs[0];
  ctx.registers[7] = regs[1];
  ctx.registers[8] = regs[2];
  ctx.registers[9] = regs[3];
  ctx.registers[2] = regs[4];
  vector<const chip8::byte*> expected = {
    ctx.pc + kPcStep, ctx.pc + kPcStep, 
    ctx.pc + kPcStep * 2, ctx.pc + kPcStep * 2, 
    ctx.pc + kPcStep * 3
  };
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<SkipIfEqValueInstruction>(input[i]);
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
