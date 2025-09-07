#include "KeybindTable.h"

#include "exception/InvalidArgumentException.h"
#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"

using namespace std;

namespace chip8 {


unordered_map<string, byte> KeybindTable::aliases = {
  {"ESC", 27},
  {"ESCAPE", 27},
  {"ENTER", 13},
  {"TAB", 9},
  {"SPACE", 32},
  {"BACKSPACE", 8},
  {"DELETE", 127},
};


KeybindTable::KeybindTable()
    : quit_key_(aliases["ESC"])
{}


void KeybindTable::setQuitKey(byte key) {
  quit_key_ = key;
}


byte KeybindTable::getQuitKey() const {
  return quit_key_;
}


void KeybindTable::bindKey(byte key, byte to) {
  checkHexKey(to);
  binds_[key] = to;
}


void KeybindTable::bindKey(const std::string& key, byte to) {
  bindKey(stringToKeyCode(key), to);
}


byte KeybindTable::operator[](byte key) const {
  if (!binds_.contains(key)) {
    throw InvalidArgumentException("Key without any bind");
  }
  return binds_.at(key);
}


const unordered_map<byte, byte>& KeybindTable::getTable() const {
  return binds_;
}


byte KeybindTable::stringToKeyCode(const std::string &s) {
  if (s.length() > 1) {
    if (aliases.contains(s)) {
      return aliases[s];
    } else {
      throw UnknownKeyException(s[0], "Unknown key alias");
    }
  } else {
    return s[0];
  }
}


void KeybindTable::checkHexKey(byte key) {
  if (key >= HexKeyboardMonitor::kNumberOfKeys) {
    throw UnknownKeyException(key, "Invalid key for keybind");
  }
}


} // namespace chip8
