#ifndef CHIP8_GRAPHICS_FRAME_H
#define CHIP8_GRAPHICS_FRAME_H

#include <string>
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

  int getWidth() const;
  int getHeight() const;

  /**
   * Draws n byte length sprite at coordinates (x, y). 
   * If sprite is positioned so part of it is outside coordinates of frame, 
   * it wraps around to the opposite side of frame.
   * @returns true if any pixel is erased.
   */
  bool draw(const byte* sprite, int n, int x0, int y0);

  /**
   * Clears frame.
   */
  void clear();

  void copy(const Frame& frame);

  std::string toString() const;

 private:
  std::vector<byte> frame_;
  int width_;
  int height_;

  bool drawAligned(const byte* sprite, int sh, int x0, int y0);
  bool drawNotAligned(const byte* sprite, int sh, int x0, int y0);
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_FRAME_H
