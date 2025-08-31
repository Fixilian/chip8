#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadRegisterInstruction.h"
#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(LoadRegisterInstructionTest, Load) {
  // Arrange
  vector<word> input = { 0x8050, 0x8160, 0x8270, 0x8380, 0x8490 };
  vector<chip8::byte> regs = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0};
  vector<chip8::byte> expected = { 0x60, 0x70, 0x80, 0x90, 0xA0 };
  int w = 16;
  int h = 5;
  int mem_size = 1024;
  int mem_reserve = 512;
  int stack_size = 16;
  vector<chip8::byte> actual(input.size());
  vector<unique_ptr<LoadRegisterInstruction>> ins(input.size());
  FixedMemory mem(mem_size, mem_reserve);
  ExecutionContext ctx(stack_size, mem, w, h);
  ctx.pc = mem.mem() + mem_reserve;
  for (size_t i = 0; i < input.size(); i += 1) {
    ins[i] = make_unique<LoadRegisterInstruction>(input[i]);
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
