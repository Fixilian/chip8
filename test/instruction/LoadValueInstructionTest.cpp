#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadValueInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(LoadValueInstructionTest, Load) {
  // Arrange
  vector<word> opcodes = { 0x6010, 0x6120, 0x6230, 0x6340, 0x6450 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContext(*mem, *keyboard);
  auto ins = createInstructions<LoadValueInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
