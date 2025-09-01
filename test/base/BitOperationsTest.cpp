#include <gtest/gtest.h>

#include <vector>

#include "base/BitOperations.h"

using namespace std;
using namespace chip8;


TEST(highest4BitsOf, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x0, 0x1, 0xA, 0xF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = highest4BitsOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(lowest12BitsOf, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x000, 0x234, 0xBCD, 0xFFF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = lowest12BitsOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(lowest8BitsOf, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x00, 0x34, 0xCD, 0xFF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = lowest8BitsOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(lowest4BitsOf, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x0, 0x4, 0xD, 0xF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = lowest4BitsOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(getXFrom, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x0, 0x2, 0xB, 0xF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = getXFrom(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(getYFrom, Correctness) {
  // Arrange
  vector<word> input = { 0x0000, 0x1234, 0xABCD, 0xFFFF };
  vector<word> expected = { 0x0, 0x3, 0xC, 0xF };
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = getYFrom(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(leastSignificantBitOf, Correctness) {
  // Arrange
  vector<chip8::byte> input = { 0b0000, 0b1111, 0b1010, 0b0101 };
  vector<chip8::byte> expected = { 0, 1, 0, 1 };
  vector<chip8::byte> actual;

  // Act
  for (auto w : input) {
    auto result = leastSignificantBitOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(mostSignificantBitOf, Correctness) {
  // Arrange
  vector<chip8::byte> input = { 0b00000000, 0b11111111, 0b10101010, 0b01010101 };
  vector<chip8::byte> expected = { 0, 1, 1, 0 };
  vector<chip8::byte> actual;

  // Act
  for (auto w : input) {
    auto result = mostSignificantBitOf(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
