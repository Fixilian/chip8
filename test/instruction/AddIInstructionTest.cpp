#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/AddIInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(AddIInstructionTest, Add) {
  // Arrange
  vector<word> opcodes = { 0xF01E, 0xF11E, 0xF21E, 0xF31E, 0xF41E };
  vector<chip8::byte> regs = { 0x10, 0x05, 0x03, 0x10, 0x30 };
  vector<word> expected = { 0x10, 0x15, 0x18, 0x28, 0x58 };
  vector<word> actual(opcodes.size());

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<AddIInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < ins.size(); i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->i;
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
