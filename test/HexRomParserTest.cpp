#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "exception/SyntaxException.h"
#include "HexRomParser.h"

using namespace std;
using namespace chip8;


TEST(HexRomParserTest, Correctness) {
  // Arrange
  string text = "0011AABB0022CCDD0033EEFF";
  vector<word> expected = { 0x0011, 0xAABB, 0x0022, 0xCCDD, 0x0033, 0xEEFF};
  vector<word> actual;
  HexRomParser parser(text);

  // Act
  word w;
  while ((w = parser.next())) {
    actual.push_back(w);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexRomParserTest, OpcodePosition) {
  // Arrange
  string text = "0011 AABB\n0022 CCDD 0033\nEEFF\n";
  vector<pair<int, int>> expected = { {1, 1}, {1, 6}, 
                                      {2, 1}, {2, 6}, {2, 11},
                                      {3, 1} };
  vector<pair<int, int>> actual;
  HexRomParser parser(text);

  // Act
  while (parser.next()) {
    actual.push_back({parser.getLine(), parser.getColumn()});
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexRomParserTest, IgnoreWhitespace) {
  // Arrange
  string text = "0011 AABB\n0022\tCCDD 0033\nEEFF\n";
  vector<word> expected = { 0x0011, 0xAABB, 0x0022, 0xCCDD, 0x0033, 0xEEFF};
  vector<word> actual;
  HexRomParser parser(text);

  // Act
  word w;
  while ((w = parser.next())) {
    actual.push_back(w);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexRomParserTest, IgnoreOneLineComment) {
  // Arrange
  string text = "0011 AABB// Hello, World!!!\n0022\tCCDD 0033\nEEFF\n";
  vector<word> expected = { 0x0011, 0xAABB, 0x0022, 0xCCDD, 0x0033, 0xEEFF};
  vector<word> actual;
  HexRomParser parser(text);

  // Act
  word w;
  while ((w = parser.next())) {
    actual.push_back(w);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexRomParserTest, IgnoreMultilineComment) {
  // Arrange
  string text = "0011 /* Hello, \n0011\n World!!! */ AABB\n0022\tCCDD 0033\n";
  vector<word> expected = { 0x0011, 0xAABB, 0x0022, 0xCCDD, 0x0033};
  vector<word> actual;
  HexRomParser parser(text);

  // Act
  word w;
  while ((w = parser.next())) {
    actual.push_back(w);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexRomParserTest, UnexpectedChar) {
  // Arrange
  string text = "00ZZ";
  HexRomParser parser(text);

  // Act
  // Assert
  EXPECT_THROW( { 
    parser.next();
  }, SyntaxException);
}


TEST(HexRomParserTest, IncorrectOpcode) {
  // Arrange
  string text = "00A";
  HexRomParser parser(text);

  // Act
  // Assert
  EXPECT_THROW( { 
    parser.next();
  }, SyntaxException);
}
