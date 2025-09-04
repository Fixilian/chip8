#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/GetSpriteLocationInstruction.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(GetSpriteLocationInstructionTest, Get) {
  // Arrange
  vector<word> opcodes = { 0xF029, 0xF129, 0xF229, 0xF329, 0xF429 };
  vector<chip8::byte> regs = { 0x00, 0x01, 0x02, 0x03, 0x04 };
  vector<word> expected(opcodes.size());
  vector<word> actual(opcodes.size());
  size_t n = opcodes.size();

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContextWithRegisters(regs, *mem, *keyboard);
  auto ins = createInstructions<GetSpriteLocationInstruction>(opcodes);

  for (size_t i = 0; i < n; i += 1) {
    auto loc = mem->getDigitSprite(regs[i]);
    expected[i] = static_cast<word>(loc - mem->mem());
  }

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
