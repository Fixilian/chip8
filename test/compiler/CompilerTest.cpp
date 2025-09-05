#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "compiler/Compiler.h"
#include "exception/SemanticException.h"

using namespace std;
using namespace chip8;


TEST(CompilerTest, Correctness) {
  // Arrange
  string text = "00E0AABB00EECCDD1133EEA1";
  vector<word> expected = { 0x00E0, 0xAABB, 0x00EE, 0xCCDD, 0x1133, 0xEEA1};
  Configuration cfg;
  bool enable_checks = true;
  Compiler compiler(cfg, enable_checks);

  // Act
  Rom rom = compiler.compile(text);

  // Assert
  size_t len = rom.size() / sizeof(word);
  const word* actual = rom.raw();
  for (size_t i = 0; i < len; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(CompilerTest, UnexpectedOpcode) {
  // Arrange
  string text = "0011";
  Configuration cfg;
  bool enable_checks = true;
  Compiler compiler(cfg, enable_checks);

  // Act
  // Assert
  EXPECT_THROW( { 
    compiler.compile(text);
  }, SemanticException);
}


TEST(CompilerTest, DisableChecks) {
  // Arrange
  string text = "0000AABB0011CCDD0033EE55";
  vector<word> expected = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55};
  Configuration cfg;
  bool enable_checks = false;
  Compiler compiler(cfg, enable_checks);

  // Act
  Rom rom = compiler.compile(text);

  // Assert
  size_t len = rom.size() / sizeof(word);
  const word* actual = rom.raw();
  for (size_t i = 0; i < len; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
