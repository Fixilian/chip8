#include <gtest/gtest.h>

#include <vector>

#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"

using namespace std;
using namespace chip8;


TEST(HexKeyboardMonitorTest, AllReleased) {
  // Arrange
  HexKeyboardMonitor keyboard;

  // Act

  // Assert
  for (chip8::byte i = 0; i < keyboard.kNumberOfKeys; i += 1) {
    EXPECT_FALSE(keyboard.pressed(i));
  }
}


TEST(HexKeyboardMonitorTest, PressRelease) {
  // Arrange
  vector<bool> expected = { 1, 0, 1, 0, 1};
  vector<bool> actual(expected.size());
  HexKeyboardMonitor keyboard;

  // Act
  for (size_t i = 0; i < expected.size(); i += 1) {
    chip8::byte key = static_cast<chip8::byte>(i);
    if (expected[i]) {
      keyboard.onKeyPressed(key);
    } else {
      keyboard.onKeyReleased(key);
    }
    actual[i] = keyboard.pressed(key);
  }

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(HexKeyboardMonitorTest, UnsupportedKey) {
  // Arrange
  HexKeyboardMonitor keyboard;

  // Act

  // Assert
  EXPECT_THROW({
    keyboard.onKeyPressed(keyboard.kNumberOfKeys + 1);
  }, UnknownKeyException);
}
