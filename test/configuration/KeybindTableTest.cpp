#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "configuration/KeybindTable.h"
#include "exception/InvalidArgumentException.h"
#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"

using namespace std;
using namespace chip8;


TEST(KeybindTableTest, Keybinds) {
  // Arrange
  KeybindTable keybinds;
  unordered_map<string, chip8::byte> binds;
  binds["a"] = 0x1;
  binds["b"] = 0x2;
  binds["c"] = 0x3;
  binds["d"] = 0xC;
  binds["e"] = 0x4;
  binds["f"] = 0x5;
  binds["g"] = 0x6;
  binds["h"] = 0xD;
  binds["i"] = 0x7;
  binds["j"] = 0x8;
  binds["k"] = 0x9;
  binds["l"] = 0xE;
  binds["m"] = 0xA;
  binds["n"] = 0x0;
  binds["o"] = 0xB;
  binds["p"] = 0xF;

  // Act
  for (const auto&[key, to] : binds) {
    keybinds.bindKey(key, to);
  } 

  // Assert
  for (const auto&[key, to] : binds) {
    chip8::byte ch = key[0];
    EXPECT_EQ(keybinds[ch], to);
  } 
  const KeybindTable& k = keybinds;
  for (const auto&[key, to] : binds) {
    chip8::byte ch = key[0];
    EXPECT_EQ(k[ch], to);
  } 
}


TEST(KeybindTableTest, StringToKeyCode) {
  // Arrange
  vector<pair<string, chip8::byte>> expected = {
    {"ESC", 27},
    {"ESCAPE", 27},
    {"ENTER", 13},
    {"TAB", 9},
    {"SPACE", 32},
    {"BACKSPACE", 8},
    {"DELETE", 127},

    {"A", 'A'}, {"B", 'B'}, {"C", 'C'}, {"D", 'D'}, {"E", 'E'},
    {"F", 'F'}, {"G", 'G'}, {"H", 'H'}, {"I", 'I'}, {"J", 'J'},
    {"K", 'K'}, {"L", 'L'}, {"M", 'M'}, {"N", 'N'}, {"O", 'O'},
    {"P", 'P'}, {"Q", 'Q'}, {"R", 'R'}, {"S", 'S'}, {"T", 'T'},
    {"U", 'U'}, {"V", 'V'}, {"W", 'W'}, {"X", 'X'}, {"Y", 'Y'},
    {"Z", 'Z'},

    {"a", 'a'}, {"b", 'b'}, {"c", 'c'}, {"d", 'd'}, {"e", 'e'},
    {"f", 'f'}, {"g", 'g'}, {"h", 'h'}, {"i", 'i'}, {"j", 'j'},
    {"k", 'k'}, {"l", 'l'}, {"m", 'm'}, {"n", 'n'}, {"o", 'o'},
    {"p", 'p'}, {"q", 'q'}, {"r", 'r'}, {"s", 's'}, {"t", 't'},
    {"u", 'u'}, {"v", 'v'}, {"w", 'w'}, {"x", 'x'}, {"y", 'y'},
    {"z", 'z'},

    {"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'},
    {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},

    {"!", '!'}, {"\"", '\"'}, {"#", '#'}, {"$", '$'}, {"%", '%'},
    {"&", '&'}, {"'", '\''}, {"(", '('}, {")", ')'}, {"*", '*'},
    {"+", '+'}, {",", ','}, {"-", '-'}, {".", '.'}, {"/", '/'},
    {":", ':'}, {";", ';'}, {"<", '<'}, {"=", '='}, {">", '>'},
    {"?", '?'}, {"@", '@'}, {"[", '['}, {"\\", '\\'}, {"]", ']'},
    {"^", '^'}, {"_", '_'}, {"`", '`'}, {"{", '{'}, {"|", '|'},
    {"}", '}'}, {"~", '~'}
  };
  vector<chip8::byte> actual(expected.size());

  // Act
  for (size_t i = 0; i < expected.size(); i += 1) {
    actual[i] = KeybindTable::stringToKeyCode(expected[i].first);
  } 

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i].second);
  } 
}


TEST(KeybindTableTest, QuitKey) {
  // Arrange
  KeybindTable keybinds;
  vector<chip8::byte> expected { 'q', 'd', '`', '~' };
  vector<chip8::byte> actual(expected.size());

  // Act
  for (size_t i = 0; i < expected.size(); i += 1) {
    keybinds.setQuitKey(expected[i]);
    actual[i] = keybinds.getQuitKey();
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
