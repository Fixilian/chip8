#ifndef CHIP8_KEYBOARD_SDLKEYADAPTER_H
#define CHIP8_KEYBOARD_SDLKEYADAPTER_H

#include <string>
#include <unordered_map>

#include "KeyAdapter.h"

namespace chip8 {

/**
 * Key adapter.
 * Сonverts key names to key codes.
 */
class SdlKeyAdapter : public KeyAdapter {
 public:
  virtual ~SdlKeyAdapter() {}

  virtual int convert(const std::string& key) const override;

  virtual const std::string& convert(int key) const override;
 private:
  static std::unordered_map<std::string, int> key_table_;
};

} // namespace chip8

#endif // CHIP8_KEYBOARD_SDLKEYADAPTER_H
