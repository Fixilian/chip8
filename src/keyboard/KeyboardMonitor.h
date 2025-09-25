#ifndef CHIP8_KEYBOARD_KEYBOARDMONITOR_H
#define CHIP8_KEYBOARD_KEYBOARDMONITOR_H

#include "base/Aliases.h"
#include "KeyListener.h"

namespace chip8 {

/**
 * Keyboard monitor interface.
 * It provides information about pressed keys and 
 * can interrupt execution until key pressed.
 */
class KeyboardMonitor : public KeyListener {
 public:
  virtual ~KeyboardMonitor() {}

  /**
   * Returns true if key pressed.
   * @returns true if key pressed.
   */
  virtual bool pressed(byte key) const = 0;
  virtual bool operator[](byte key) const = 0;

  /**
   * Waits until key pressed and returns key.
   * @returns pressed key.
   * @throws UnknownKeyException when key is unsupported.
   */
  virtual byte waitKeyPress() = 0;
};

} // namespace chip8

#endif // CHIP8_KEYBOARD_KEYBOARDMONITOR_H
