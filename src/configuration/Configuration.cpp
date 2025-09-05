#include "Configuration.h"

#include <unordered_set>

#include "exception/InvalidArgumentException.h"
#include "exception/InvalidConfigException.h"
#include "exception/UnknownKeyException.h"
#include "keyboard/HexKeyboardMonitor.h"

using namespace std;

namespace chip8 {

constexpr int kDefaultMemorySize = 4096;
constexpr int kDefaultReservedMemorySize = 512;
constexpr int kDefaultStackSize = 16;
constexpr int kDefaultDisplayWidth = 64;
constexpr int kDefaultDisplayHeight = 32;
constexpr int kDefaultTimerFrequency = 60;
constexpr int kMaxTimerFrequency = 500;


Configuration::Configuration() 
    : memory_size_(kDefaultMemorySize),
      reserved_memory_size_(kDefaultReservedMemorySize),
      stack_size_(kDefaultStackSize),
      display_width_(kDefaultDisplayWidth),
      display_height_(kDefaultDisplayHeight),
      timer_frequency_(kDefaultTimerFrequency)
{
  // 16-key keypad
  // 1 2 3 C
  // 4 5 6 D
  // 7 8 9 E
  // A 0 B F

  // default keybinds for WASD keyboards
  keybinds_['1'] = 0x1;
  keybinds_['2'] = 0x2;
  keybinds_['3'] = 0x3;
  keybinds_['4'] = 0xC;
  keybinds_['q'] = 0x4;
  keybinds_['w'] = 0x5;
  keybinds_['e'] = 0x6;
  keybinds_['r'] = 0xD;
  keybinds_['a'] = 0x7;
  keybinds_['s'] = 0x8;
  keybinds_['d'] = 0x9;
  keybinds_['f'] = 0xE;
  keybinds_['z'] = 0xA;
  keybinds_['x'] = 0x0;
  keybinds_['c'] = 0xB;
  keybinds_['v'] = 0xF;
}


void Configuration::setMemorySize(int size) {
  if (size < kDefaultMemorySize) {
    throw InvalidArgumentException("Memory size must be >= 4096");
  }
  memory_size_ = size;
}


int Configuration::getMemorySize() const {
  return memory_size_;
}


void Configuration::setReservedMemorySize(int size) {
  if (size < kDefaultReservedMemorySize) {
    throw InvalidArgumentException("Reserved memory size must be >= 512");
  }
  reserved_memory_size_ = size;
}


int Configuration::getReservedMemorySize() const {
  return reserved_memory_size_;
}


void Configuration::setStackSize(int size) {
  if (size < kDefaultStackSize) {
    throw InvalidArgumentException("Stack size must be >= 16");
  }
  stack_size_ = size;
}


int Configuration::getStackSize() const {
  return stack_size_;
}


void Configuration::setDisplayWidth(int width) {
  if (width < kDefaultDisplayWidth) {
    throw InvalidArgumentException("Display width must be >= 64");
  }
  display_width_ = width;
}


int Configuration::getDisplayWidth() const {
  return display_width_;
}


void Configuration::setDisplayHeight(int height) {
  if (height < kDefaultDisplayHeight) {
    throw InvalidArgumentException("Display height must be >= 32");
  }
  display_height_ = height;
}


int Configuration::getDisplayHeight() const {
  return display_height_;
}


void Configuration::setTimerFrequency(int freq) {
  if (freq < kDefaultTimerFrequency || freq > kMaxTimerFrequency) {
    throw InvalidArgumentException("Timer frequency must be >= 60 and <= 500");
  }
  timer_frequency_ = freq;
}


int Configuration::getTimerFrequency() const {
  return timer_frequency_;
}


void Configuration::bindKey(byte key, byte to) {
  if (to >= HexKeyboardMonitor::kNumberOfKeys) {
    throw UnknownKeyException(to, "Invalid key for keybind");
  }
  byte old_bind_key = 0;
  bool found = false;;
  for (const auto&[k, t] : keybinds_) {
    if (t == to) {
      old_bind_key = k;
      found = true;
      break;
    }
  }
  if (found) {
    auto old_bind = keybinds_.find(old_bind_key);
    keybinds_.erase(old_bind);
  }
  keybinds_[key] = to;
}


const std::unordered_map<byte, byte>& Configuration::getKeybinds() const {
  validateKeybinds();
  return keybinds_;
}


void Configuration::validateKeybinds() const {
  unordered_set<byte> used_keys;
  for (const auto&[_, to] : keybinds_) {
    used_keys.insert(to);
  }
  if (used_keys.size() != HexKeyboardMonitor::kNumberOfKeys) {
    throw InvalidConfigException("Not all keys have bind");
  }
}


} // namespace chip8
