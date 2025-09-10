#ifndef CHIP8_CONFIGURATION_KEYBINDTABLE_H
#define CHIP8_CONFIGURATION_KEYBINDTABLE_H

#include <memory>
#include <string>
#include <unordered_map>

#include "base/Aliases.h"
#include "keyboard/KeyAdapter.h"

namespace chip8 {

/**
 * Key bind table.
 * Contains bindings for keys of 16-key keypad and quit key code. 
 */
class KeybindTable {
 public:
  KeybindTable();

  KeybindTable(const KeybindTable&) = default;
  KeybindTable& operator=(const KeybindTable&) = default;
  KeybindTable(KeybindTable&&) = default;
  KeybindTable& operator=(KeybindTable&&) = default;

  void setQuitKey(const std::string& key);
  void setQuitKey(int key);
  int getQuitKey() const;

  /**
   * @throws UnknownKeyException when 'to' is invalid key. 
   */
  void bindKey(int key, byte to);
  void bindKey(const std::string& key, byte to);

  /**
   * @throws InvalidArgumentException when key is not bound
   */
  byte operator[](int key) const;

  const std::unordered_map<int, byte>& getTable() const;

  const KeyAdapter& getAdapter() const;

 private:
  std::unordered_map<int, byte> binds_;
  std::shared_ptr<KeyAdapter> adapter_;
  int quit_key_;

  void checkHexKey(byte key);
};

} // namespace chip8

#endif // CHIP8_CONFIGURATION_KEYBINDTABLE_H
