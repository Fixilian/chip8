#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "configuration/KeybindTable.h"
#include "exception/InvalidArgumentException.h"
#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"
#include "keyboard/SdlKeyAdapter.h"

using namespace std;
using namespace chip8;


TEST(KeybindTableTest, Keybinds) {
  // Arrange
  KeybindTable keybinds;
  auto& adapter = keybinds.getAdapter();
  unordered_map<string, chip8::byte> binds;
  binds["A"] = 0x1;
  binds["B"] = 0x2;
  binds["C"] = 0x3;
  binds["D"] = 0xC;
  binds["E"] = 0x4;
  binds["F"] = 0x5;
  binds["G"] = 0x6;
  binds["H"] = 0xD;
  binds["I"] = 0x7;
  binds["J"] = 0x8;
  binds["K"] = 0x9;
  binds["L"] = 0xE;
  binds["M"] = 0xA;
  binds["N"] = 0x0;
  binds["O"] = 0xB;
  binds["P"] = 0xF;

  // Act
  for (const auto&[key, to] : binds) {
    keybinds.bindKey(key, to);
  } 

  // Assert
  for (const auto&[key, to] : binds) {
    EXPECT_EQ(keybinds[adapter.convert(key)], to);
  } 
  const KeybindTable& k = keybinds;
  for (const auto&[key, to] : binds) {
    EXPECT_EQ(k[adapter.convert(key)], to);
  } 
}


TEST(KeybindTableTest, QuitKey) {
  // Arrange
  KeybindTable keybinds;
  vector<string> expected { "Q", "D", ",", ".", "ESCAPE" };
  vector<string> actual(expected.size());
  auto& adapter = keybinds.getAdapter();

  // Act
  for (size_t i = 0; i < expected.size(); i += 1) {
    keybinds.setQuitKey(expected[i]);
    actual[i] = adapter.convert(keybinds.getQuitKey());
  } 

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  } 
}


TEST(KeybindTableTest, Exceptions) {
  // Arrange
  KeybindTable keybinds;

  // Act

  // Assert
  EXPECT_THROW({
    auto b = keybinds['a'];
    (void) b;
  }, InvalidArgumentException);

  EXPECT_THROW({
    keybinds.bindKey('a', HexKeyboardMonitor::kNumberOfKeys);
  }, UnknownKeyException);
}
