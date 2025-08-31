#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/SkipIfEqRegisterInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(SkipIfEqRegisterInstructionTest, Skip) {
  // Arrange
  vector<word> input = { 0x5010, 0x5130, 0x5210, 0x5240, 0x5340 };
  vector<chip8::byte> regs = { 0x20, 0x01, 0x99, 0x01, 0x99 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<const chip8::byte*> actual(input.size());
  vector<unique_ptr<SkipIfEqRegisterInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  vector<const chip8::byte*> expected = {
    ctx.pc, ctx.pc + kPcStep, 
    ctx.pc + kPcStep, ctx.pc + kPcStep * 2, 
    ctx.pc + kPcStep * 2
  };
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<SkipIfEqRegisterInstruction>(input[i]);
    ctx.registers[i] = regs[i];
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
