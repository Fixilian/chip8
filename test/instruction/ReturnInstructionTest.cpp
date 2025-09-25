#include "InstructionFixture.h"

#include "instruction/ReturnInstruction.h"


TEST_F(InstructionTest, Return) {
  // Arrange
  vector<word> input = { 600, 700, 800, 900, 1000 };
  vector<const chip8::byte*> expected(input.size());
  vector<const chip8::byte*> actual(input.size());
  size_t n = input.size();
  setupContext();
  ReturnInstruction ret_ins(0x00EE);

  for (size_t i = 0; i < n; i += 1) {
    ctx->stack.push(input[i]);
    expected[i] = mem->mem() + input[i];
  }

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ret_ins.execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[n - 1 - i]);
  }
}
