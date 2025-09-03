#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(LoadInstructionTest, Load) {
  // Arrange
  int mem_size = 1024;
  int mem_reserve = 512;
  LoadInstruction ins(0xF965);
  vector<chip8::byte> expected = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255 };
  int n = static_cast<int>(expected.size());

  auto keyboard = generateKeyboardMonitor();
  auto mem = generateMemory(mem_size, mem_reserve);
  auto ctx = generateContext(*mem, *keyboard);
  ctx->i = static_cast<word>(mem_reserve);
  for (int i = 0; i < n; i += 1) {
    ctx->ram[ctx->i + i] = expected[i];
  }

  // Act
  ins.execute(*ctx);

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(ctx->registers[i], expected[i]);
  }
}
