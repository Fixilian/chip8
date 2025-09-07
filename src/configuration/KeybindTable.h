#ifndef CHIP8_CONFIGURATION_KEYBINDTABLE_H
#define CHIP8_CONFIGURATION_KEYBINDTABLE_H

#include <string>
#include <unordered_map>

#include "base/Aliases.h"

namespace chip8 {

/**
 * Key bind table.
 * Contains bindings for keys of 16-key keypad and quit key code. 
 */
class KeybindTable {
 public:
  static std::unordered_map<std::string, byte> aliases;

  KeybindTable();

  KeybindTable(const KeybindTable&) = default;
  KeybindTable& operator=(const KeybindTable&) = default;
  KeybindTable(KeybindTable&&) = default;
  KeybindTable& operator=(KeybindTable&&) = default;

  void setQuitKey(byte key);
  byte getQuitKey() const;

  /**
   * @throws UnknownKeyException when 'to' is invalid key. 
   */
  void bindKey(byte key, byte to);
  void bindKey(const std::string& key, byte to);

  /**
   * @throws InvalidArgumentException when key is not bound
   */
  byte operator[](byte key) const;

  const std::unordered_map<byte, byte>& getTable() const;

  /**
   * Converts string representation of code to actual key code.
   * Not supports arrows and functional keys (F1, F2, etc...).
   */
  static byte stringToKeyCode(const std::string &s);

 private:
  std::unordered_map<byte, byte> binds_;
  byte quit_key_;

  void checkHexKey(byte key);
};

} // namespace chip8

#endif // CHIP8_CONFIGURATION_KEYBINDTABLE_H
