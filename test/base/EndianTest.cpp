#include <gtest/gtest.h>

#include <vector>

#include "base/Aliases.h"
#include "base/Endian.h"

using namespace std;
using namespace chip8;


TEST(byteSwapTo, 2Bytes) {
  // Arrange
  vector<word> input = {0x0000, 0x1122, 0xAABB, 0xFFFF};
  vector<word> expected = {0x0000, 0x2211, 0xBBAA, 0xFFFF};
  vector<word> actual;

  // Act
  for (auto w : input) {
    word result = byteSwapTo<Endianness::BigEndian>(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(byteSwapTo, 4Bytes) {
  // Arrange
  vector<unsigned int> input = {0x0000000, 0x11223344, 0xAABBCCDD, 0xFFFFFFFF};
  vector<unsigned int> expected = {0x00000000, 0x44332211, 0xDDCCBBAA, 0xFFFFFFFF};
  vector<unsigned int> actual;

  // Act
  for (auto w : input) {
    unsigned int result = byteSwapTo<Endianness::BigEndian>(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(byteSwapTo, 8Bytes) {
  // Arrange
  vector<unsigned long long> input = {0x1122334455667788, 0x99AABBCCDDEEFF11};
  vector<unsigned long long> expected = {0x8877665544332211, 0x11FFEEDDCCBBAA99};
  vector<unsigned long long> actual;

  // Act
  for (auto w : input) {
    unsigned long long result = byteSwapTo<Endianness::BigEndian>(w);
    actual.push_back(result);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
