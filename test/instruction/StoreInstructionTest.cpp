#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/StoreInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(StoreInstructionTest, Store) {
  // Arrange
  int mem_size = 1024;
  int mem_reserve = 512;
  StoreInstruction ins(0xF955);
  vector<chip8::byte> regs = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255 };
  int n = static_cast<int>(regs.size());

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory(mem_size, mem_reserve);
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  ctx->i = static_cast<word>(mem_reserve);

  // Act
  ins.execute(*ctx);

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(ctx->ram[ctx->i + i], regs[i]);
  }
}
