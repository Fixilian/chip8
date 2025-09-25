#ifndef CHIP8_KEYBOARD_KEYLISTENER_H
#define CHIP8_KEYBOARD_KEYLISTENER_H

#include "base/Aliases.h"

namespace chip8 {

/**
 * Key listener interface
 */
class KeyListener {
 public:
  virtual ~KeyListener() {}

  /**
   * Callback for key pressed event.
   * @throws UnknownKeyException when key is unsupported.
   */
  virtual void onKeyPressed(byte key) = 0;

  /**
   * Callback for key released event
   * @throws UnknownKeyException when key is unsupported.
   */
  virtual void onKeyReleased(byte key) = 0;
};

} // namespace chip8

#endif // CHIP8_KEYBOARD_KEYLISTENER_H
