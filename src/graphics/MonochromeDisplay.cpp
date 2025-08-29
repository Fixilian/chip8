#include "MonochromeDosplay.h"

namespace chip8 {


MonochromeDisplay::MonochromeDisplay(int w, int h, const Frame& frame)
    : width_(w),
      height_(h),
      frame_(frame)
{}


int MonochromeDisplay::getHeight() {
  return height_;
}


int MonochromeDisplay::getWidth() {
  return width_;
}


const Frame& MonochromeDisplay::getFrame() {
  return frame_;
}


} // namespace chip8
