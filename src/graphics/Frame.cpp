#include "Frame.h"

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


Frame::Frame(int w, int h) 
    : frame_(h * w / kBits),
      width_(w),
      height_(h)
{}

 
byte Frame::getByte(int x, int y) const {
  int w = width_ / kBits;
  return frame_[x + y * w];
}


void Frame::setByte(int x, int y, byte val) {
  int w = width_ / kBits;
  frame_[x + y * w] = val;
}


byte Frame::getPixel(int x, int y) const {
  byte b = getByte(x / kBits, y);
  byte pos = kBits - (x % kBits) - 1;
  byte val = b & (1 << pos);
  return val >> pos;
}


void Frame::setPixel(int x, int y, byte val) {
  byte b = getByte(x / kBits, y);
  byte pos = kBits - (x % kBits) - 1;
  if (val) {
    b |= (1 << pos);
  } else {
    b = static_cast<byte>(b & ~(1 << pos));
  }
  setByte(x / kBits, y, b);
}


void Frame::clear() {
  for (auto& x : frame_) {
    x = 0;
  }
}


} // namespace chip8
