#include "InstructionFixture.h"

#include "instruction/StoreBcdInstruction.h"


TEST_F(InstructionTest, StoreBcd) {
  // Arrange
  int mem_size = 1024;
  int mem_reserve = 512;
  int mem_step = 3;
  word start_addr = static_cast<word>(mem_reserve);
  vector<word> opcodes = { 0xF033, 0xF133, 0xF233, 0xF333, 0xF433, 
                            0xF533, 0xF633, 0xF733, 0xF833, 0xF933 };
  vector<chip8::byte> regs = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255 };
  vector<chip8::byte> expected1 = { 0, 0, 0, 0, 0, 0,  0,  0,  1,   2 };
  vector<chip8::byte> expected2 = { 0, 0, 0, 0, 0, 1,  3,  6,  2,   5 };
  vector<chip8::byte> expected3 = { 0, 1, 2, 4, 8, 6,  2,  4,  8,   5 };
  vector<chip8::byte> actual1(regs.size());
  vector<chip8::byte> actual2(regs.size());
  vector<chip8::byte> actual3(regs.size());
  int n = static_cast<int>(opcodes.size());
  setupContextWithMemory<StoreBcdInstruction>(mem_size, mem_reserve, regs, opcodes);

  // Act
  for (int i = 0; i < n; i += 1) {
    int offset = start_addr + i * mem_step;
    ctx->i = static_cast<word>(offset);
    ins[i]->execute(*ctx);
    actual1[i] = ctx->ram[ctx->i];
    actual2[i] = ctx->ram[ctx->i + 1];
    actual3[i] = ctx->ram[ctx->i + 2];
  }

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(actual1[i], expected1[i]);
    EXPECT_EQ(actual2[i], expected2[i]);
    EXPECT_EQ(actual3[i], expected3[i]);
  }
}
