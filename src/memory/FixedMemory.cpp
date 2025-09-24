#include "FixedMemory.h"

#include <cstring>
#include <sstream>

#include "base/Log.h"
#include "exception/SegFaultException.h"
#include "exception/OutOfRangeException.h"

using namespace std;

namespace chip8 {


FixedMemory::FixedMemory(int size, int reserve)
    : size_(size),
      reserve_(reserve),
      user_mem_begin_(reserve),
      sys_mem_protection_enabled_(true),
      mem_(new byte[size]),
      rom_begin_(nullptr),
      rom_end_(nullptr),
      sprites_(nullptr)
{
  constexpr int kSourceSize = 80; 
  byte source[kSourceSize] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
  };
  sprites_ = mem_;
  for (int i = 0; i < kSourceSize; i += 1) {
    sprites_[i] = source[i];
  }
}


FixedMemory::~FixedMemory() {
  delete[] mem_;
  mem_ = nullptr;
}


void FixedMemory::load(const Rom& rom) {
  rom_begin_ = mem_ + reserve_;
  rom_end_ = mem_ + reserve_ + rom.size();
  user_mem_begin_ += rom.size();
  memcpy(rom_begin_, rom.raw(), rom.size());
}


const byte* FixedMemory::getUserSpaceBegin() {
  return mem_ + user_mem_begin_;
}


const byte* FixedMemory::getRomBegin() {
  return rom_begin_;
}


const byte* FixedMemory::getRomEnd() {
  return rom_end_;
}


byte& FixedMemory::operator[](int index) {
  if (sys_mem_protection_enabled_) {
    if (index < reserve_ || index >= size_) {
      throw SegFaultException("Attempt to access system memory");
    }
    if (index < user_mem_begin_) {
      Log::warn("Rewriting rom in runtime");
    }
  }
  return mem_[index];
}


const byte& FixedMemory::operator[](int index) const {
  return mem_[index];
}


bool FixedMemory::isSysMemoryProtectionEnabled() const {
  return sys_mem_protection_enabled_;
}


void FixedMemory::setSysMemoryProtectionEnabled(bool val) {
  sys_mem_protection_enabled_ = val;
}


const byte* FixedMemory::getDigitSprite(int digit) {
  if (digit < 0 || digit > 0xF) {
    throw OutOfRangeException("Unexpected value for hex digit");
  }
  return sprites_ + (digit * kDigitSpriteSize);
}


const byte* FixedMemory::mem() const {
  return mem_;
}


string FixedMemory::toString() const {
  stringstream stream;
  stream << "Memory [size=" << size_ << ", reserve=" << reserve_;
  stream << ", user_space_begin=" << user_mem_begin_ << "]";
  return stream.str();
}


void FixedMemory::setSprite(byte* p, byte b0, byte b1, byte b2, byte b3, byte b4) {
  p[0] = b0;
  p[1] = b1;
  p[2] = b2;
  p[3] = b3;
  p[4] = b4;
}
  

} // namespace chip8
