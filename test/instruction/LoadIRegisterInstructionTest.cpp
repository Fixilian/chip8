#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"
#include "instruction/LoadIRegisterInstruction.h"
#include "InstructionTestBase.h"

using namespace std;
using namespace chip8;


TEST(LoadIRegisterInstructionTest, Load) {
  // Arrange
  vector<word> opcodes = { 0xA050, 0xA160, 0xA270, 0xA380, 0xA490 };
  vector<word> expected = { 0x0050, 0x0160, 0x0270, 0x0380, 0x0490 };
  vector<word> actual(opcodes.size());
  size_t n = opcodes.size();

  auto mem = generateMemory();
  auto ctx = generateContext(*mem);
  auto ins = generateInstructions<LoadIRegisterInstruction>(opcodes);

  // Act
  for (size_t i = 0; i < n; i += 1) {
    ins[i]->execute(*ctx);
    actual[i] = ctx->i;
  }

  // Assert
  for (size_t i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
