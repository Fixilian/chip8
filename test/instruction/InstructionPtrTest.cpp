#include <gtest/gtest.h>

#include <vector>

#include "base/Allocator.h"
#include "instruction/InstructionPtr.h"
#include "instruction/Instructions.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(InstructionPtrTest, CreateStoreInstruction) {
  // Arrange
  int block_size = sizeof(Instruction);
  int block_count = 4;
  int mem_size = 1024;
  int mem_reserve = 512;
  Allocator allocator(block_size, block_count);
  auto ins = InstructionPtr::create<StoreInstruction>(0xF955, allocator);
  vector<chip8::byte> regs = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255 };
  int n = static_cast<int>(regs.size());

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory(mem_size, mem_reserve);
  auto ctx = generateContextWithRegisters(regs, *mem, *keyboard);
  ctx->i = static_cast<word>(mem_reserve);

  // Act
  ins->execute(*ctx);

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(ctx->ram[ctx->i + i], regs[i]);
  }
}
