#include <gtest/gtest.h>

#include <vector>

#include "exception/UnknownKeyException.h"
#include "keyboard/SdlKeyAdapter.h"

using namespace std;
using namespace chip8;


TEST(SdlKeyAdapterTest, Convert) {
  // Arrange
  SdlKeyAdapter adapter;
  vector<string> expected = {
    "A", 
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",

    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
  };
  vector<string> actual(expected.size());

  // Act
  for (size_t i = 0; i < expected.size(); i += 1) {
    int key_code = adapter.convert(expected[i]);
    actual[i] = adapter.convert(key_code);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
