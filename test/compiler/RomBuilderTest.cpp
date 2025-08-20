#include <gtest/gtest.h>

#include <vector>

#include "compiler/RomBuilder.h"

using namespace std;
using namespace chip8;


TEST(RomBuilderTest, Correctness) {
  // Arrange
  vector<word> expected = { 0x0011, 0xAABB, 0x0022, 0xCCDD, 0x0033, 0xEEFF};
  RomBuilder builder(expected.size() * sizeof(word));

  // Act
  for (word w : expected) {
    builder.push(w);
  }
  Rom rom = builder.build();

  // Assert
  size_t len = rom.size() / sizeof(word);
  const word* actual = rom.raw();
  for (size_t i = 0; i < len; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
