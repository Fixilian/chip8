#ifndef CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H
#define CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H

#include "Display.h"
#include "Frame.h"

namespace chip8 {

class MonochromeDisplay : Display {
 public:
  MonochromeDisplay(int w, int h, const Frame& frame); 

  virtual ~MonochromeDisplay() {}

  virtual int getHeight() override;
  virtual int getWidth() override;

  virtual const Frame& getFrame() override;

 private:
  int width_;
  int height_;
  const Frame& frame_;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H
