#ifndef CHIP8_KEYBOARD_HEXKEYBOARDMONITOR_H
#define CHIP8_KEYBOARD_HEXKEYBOARDMONITOR_H

#include <condition_variable>
#include <mutex>
#include <vector>

#include "base/Aliases.h"
#include "KeyboardMonitor.h"

namespace chip8 {

/**
 * 16-key hexadecimal keyboard monitor.
 */
class HexKeyboardMonitor : public KeyboardMonitor {
 public:
  static constexpr byte kNumberOfKeys = 16; 

  HexKeyboardMonitor();

  virtual ~HexKeyboardMonitor() {}

  virtual void onKeyPressed(byte key) override;

  virtual void onKeyReleased(byte key) override;

  virtual bool pressed(byte key) const override;
  virtual bool operator[](byte key) const override;

  virtual byte waitKeyPress() override;

 private:
  std::vector<bool> pressed_;
  std::condition_variable cv_;
  std::mutex mtx_;
  bool key_pressed_;
  byte last_pressed_key_;

  void checkKey(byte key);
};

} // namespace chip8

#endif // CHIP8_KEYBOARD_HEXKEYBOARDMONITOR_H