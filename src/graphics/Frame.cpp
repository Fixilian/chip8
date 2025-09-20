#include "Frame.h"

#include <algorithm>
#include <sstream>

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
  byte pos = x % kBits;
  return getBit(b, pos);
}


void Frame::setPixel(int x, int y, byte val) {
  byte b = getByte(x / kBits, y);
  byte pos = x % kBits;
  b = setBit(b, pos, val);
  setByte(x / kBits, y, b);
}


bool Frame::draw(const byte* sprite, int n, int x0, int y0) {
  int sw = kBits;
  int sh = n;
  if (x0 % sw == 0) {
    return drawAligned(sprite, sh, x0 / sw, y0);
  } else {
    return drawNotAligned(sprite, sh, x0, y0);
  }
}


void Frame::clear() {
  for (auto& x : frame_) {
    x = 0;
  }
}


void Frame::copy(const Frame& frame) {
  std::copy(frame.frame_.begin(), frame.frame_.end(), frame_.begin());
}


string Frame::toString() const {
  stringstream stream;
  for (int y = 0; y < height_; y += 1) {
    for (int x = 0; x < width_; x += 1) {
      auto pixel = getPixel(x, y);
      if (pixel) {
        stream << '0';
      } else {
        stream << '-';
      }
    }
    stream << '\n';
  }
  return stream.str();
}


bool Frame::drawAligned(const byte* sprite, int sh, int x0, int y0) {
  bool collision_happened = false;
  for (int y = 0; y < sh; y += 1) {
    byte s = sprite[y];
    byte f = getByte(x0, y0 + y);
    byte nbyte = f ^ s;
    if (nbyte ^ s) {
      collision_happened = true;
    }
    setByte(x0, y0 + y, nbyte);
  }
  return collision_happened;
}


bool Frame::drawNotAligned(const byte* sprite, int sh, int x0, int y0) {
  int sw = kBits;
  bool collision_happened = false;
  for (int y = 0; y < sh; y += 1) {
    byte s = sprite[y];
    for (int x = 0; x < sw; x += 1) {
      byte spixel = getBit(s, x);
      int fx = (x + x0) % width_;
      int fy = (y + y0) % height_;
      byte fpixel = getPixel(fx, fy);
      byte npixel = spixel ^ fpixel;
      if (npixel ^ spixel) {
        collision_happened = true;
      }
      setPixel(fx, fy, npixel);
    }
  }
  return collision_happened;
}


} // namespace chip8
