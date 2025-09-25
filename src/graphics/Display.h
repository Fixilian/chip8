#ifndef CHIP8_GRAPHICS_DISPLAY_H
#define CHIP8_GRAPHICS_DISPLAY_H

#include "Frame.h"

namespace chip8 {

/**
 * Display interface.
 */
class Display {
 public:
  virtual ~Display() {}

  virtual bool init() = 0;

  virtual void render(const Frame& frame) = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_DISPLAY_H
