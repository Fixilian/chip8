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

  virtual int getHeight() = 0;
  virtual int getWidth() = 0;

  virtual const Frame& getFrame() = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_DISPLAY_H
