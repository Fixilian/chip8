#ifndef CHIP8_GRAPHICS_FRAMELISTENER_H
#define CHIP8_GRAPHICS_FRAMELISTENER_H

#include "Frame.h"

namespace chip8 {

class FrameListener {
 public:
  virtual ~FrameListener() {}

  virtual void onChange(const Frame& frame) = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_FRAMELISTENER_H
