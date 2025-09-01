#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/RandomInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(RandomInstruction, Jump) {
  // Arrange
  vector<word> opcodes = { 0xC013, 0xC124, 0xC235, 0xC346, 0xC457 };
  vector<chip8::byte> regs = { 0xF0, 0xF1, 0x01, 0x40, 0xD0, 0x60};
  vector<chip8::byte> expected = {0x13, 0x24, 0x35, 0x46, 0x57};
  vector<chip8::byte> actual(opcodes.size());
  size_t n = opcodes.size();

  auto mem = generateMemory();
  auto ctx = generateContextWithRegisters(regs, *mem);
  auto ins = generateInstructions<RandomInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->registers[i];
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_LE(actual[i], expected[i]);
  }
}
