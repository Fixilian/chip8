#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadDtInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(LoadDtInstructionTest, Load) {
  // Arrange
  vector<word> opcodes = { 0xF007, 0xF107, 0xF207, 0xF307, 0xF407 };
  vector<chip8::byte> expected = { 0x10, 0x20, 0x30, 0x40, 0x50 };
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContext(*mem, *keyboard);
  auto ins = createInstructions<LoadDtInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ctx->setDt(expected[i]);
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
