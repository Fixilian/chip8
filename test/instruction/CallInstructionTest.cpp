#include "InstructionFixture.h"

#include "base/BitOperations.h"
#include "instruction/CallInstruction.h"


TEST_F(InstructionTest, Call) {
  // Arrange
  vector<word> opcodes = { 0x2600, 0x2700, 0x2800, 0x2900, 0x2999 };
  vector<const chip8::byte*> expected(opcodes.size());
  vector<word> expected_stack(opcodes.size());
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<CallInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    word jmp = lowest12BitsOf(opcodes[i]);
    expected[i] = mem->mem() + jmp;
  }
  for (size_t i = 0; i < n - 1; i += 1) {
    expected_stack[n - 2 - i] = lowest12BitsOf(opcodes[i]);
  }
  expected_stack[n - 1] = static_cast<word>(ctx->pc - mem->mem());

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
  for (size_t i = 0; i < n; i += 1) {
    word stack_top = ctx->stack.pop();
    EXPECT_EQ(stack_top, expected_stack[i]);
  }
}
