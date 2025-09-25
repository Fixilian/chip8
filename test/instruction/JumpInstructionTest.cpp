#include "InstructionFixture.h"

#include "base/BitOperations.h"
#include "instruction/JumpInstruction.h"


TEST_F(InstructionTest, Jump) {
  // Arrange
  vector<word> opcodes = { 0x1600, 0x1700, 0x1800, 0x1900, 0x1999 };
  vector<const chip8::byte*> expected(opcodes.size());
  vector<const chip8::byte*> actual(opcodes.size());
  size_t n = opcodes.size();
  setupContext<JumpInstruction>(opcodes);
  
  for (size_t i = 0; i < n; i += 1) {
    word jmp = lowest12BitsOf(opcodes[i]);
    expected[i] = mem->mem() + jmp;
  }

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->pc;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
