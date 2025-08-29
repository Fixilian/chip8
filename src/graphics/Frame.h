#ifndef CHIP8_GRAPHICS_FRAME_H
#define CHIP8_GRAPHICS_FRAME_H

#include <vector>

#include "base/Aliases.h"

namespace chip8 {

/**
 * Monochrome frame. 
 * 1 pixel = 1 bit.
 */
class Frame {
 public:
  /**
   * @param w - width in pixels.
   * @param h - height.
   */
  Frame(int w, int h);

  Frame(const Frame&) = default;
  Frame& operator=(const Frame&) = default;
  Frame(Frame&&) = default;
  Frame& operator=(Frame&&) = default;

  byte getByte(int x, int y) const;
  void setByte(int x, int y, byte val);

  byte getPixel(int x, int y) const;
  void setPixel(int x, int y, byte val);

 private:
  std::vector<byte> frame_;
  int width_;
  int height_;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_FRAME_H
