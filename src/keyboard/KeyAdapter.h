#ifndef CHIP8_KEYBOARD_KEYADAPTER_H
#define CHIP8_KEYBOARD_KEYADAPTER_H

#include <string>

#include "base/Aliases.h"

namespace chip8 {

/**
 * Key adapter.
 * Сonverts key names to key codes.
 */
class KeyAdapter {
 public:
  virtual ~KeyAdapter() {}

  /**
   * @throw UnknownKeyException when key is unknown.
   */
  virtual int convert(const std::string& key) const = 0;

  virtual const std::string& convert(int key) const = 0;
};

} // namespace chip8

#endif // CHIP8_KEYBOARD_KEYLISTENER_H
