#include "InstructionFixture.h"

#include "instruction/StoreInstruction.h"


TEST_F(InstructionTest, Store) {
  // Arrange
  int mem_size = 1024;
  int mem_reserve = 512;
  StoreInstruction ins(0xF955);
  vector<chip8::byte> regs = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255 };
  int n = static_cast<int>(regs.size());
  setupContextWithMemory(mem_size, mem_reserve, regs);
  ctx->i = static_cast<word>(mem_reserve);

  // Act
  ins.execute(*ctx);

  // Assert
  ctx->i = static_cast<word>(mem_reserve);
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(ctx->ram[ctx->i + i], regs[i]);
  }
}
