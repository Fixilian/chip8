#include "KeybindTable.h"

#include "exception/InvalidArgumentException.h"
#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"
#include "keyboard/SdlKeyAdapter.h"

using namespace std;

namespace chip8 {


KeybindTable::KeybindTable()
    : adapter_(make_shared<SdlKeyAdapter>()),
      quit_key_(adapter_->convert("ESCAPE"))
{}


void KeybindTable::setQuitKey(const std::string& key) {
  quit_key_ = adapter_->convert(key);
}


void KeybindTable::setQuitKey(int key) {
  quit_key_ = key;
}


int KeybindTable::getQuitKey() const {
  return quit_key_;
}


void KeybindTable::bindKey(int key, byte to) {
  checkHexKey(to);
  binds_[key] = to;
}


void KeybindTable::bindKey(const std::string& key, byte to) {
  int key_code = adapter_->convert(key);
  bindKey(key_code, to);
}


byte KeybindTable::operator[](int key) const {
  if (!binds_.contains(key)) {
    throw InvalidArgumentException("Key without any bind");
  }
  return binds_.at(key);
}


bool KeybindTable::contains(int key) const {
  return binds_.contains(key);
}


const unordered_map<int, byte>& KeybindTable::getTable() const {
  return binds_;
}


const KeyAdapter& KeybindTable::getAdapter() const {
  return *adapter_;
}


void KeybindTable::checkHexKey(byte key) {
  if (key >= HexKeyboardMonitor::kNumberOfKeys) {
    throw UnknownKeyException(key, "Invalid key for keybind");
  }
}


} // namespace chip8
