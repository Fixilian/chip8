#include "MachineSpecification.h"

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


MachineSpecification::MachineSpecification() 
    : memory_size_(kDefaultMemorySize),
      reserved_memory_size_(kDefaultReservedMemorySize),
      stack_size_(kDefaultStackSize),
      display_width_(kDefaultDisplayWidth),
      display_height_(kDefaultDisplayHeight),
      timer_frequency_(kDefaultTimerFrequency)
{}


void MachineSpecification::setMemorySize(int size) {
  if (size < kDefaultMemorySize) {
    throw InvalidArgumentException("Memory size must be >= 4096");
  }
  memory_size_ = size;
}


int MachineSpecification::getMemorySize() const {
  return memory_size_;
}


void MachineSpecification::setReservedMemorySize(int size) {
  if (size < kDefaultReservedMemorySize) {
    throw InvalidArgumentException("Reserved memory size must be >= 512");
  }
  reserved_memory_size_ = size;
}


int MachineSpecification::getReservedMemorySize() const {
  return reserved_memory_size_;
}


void MachineSpecification::setStackSize(int size) {
  if (size < kDefaultStackSize) {
    throw InvalidArgumentException("Stack size must be >= 16");
  }
  stack_size_ = size;
}


int MachineSpecification::getStackSize() const {
  return stack_size_;
}


void MachineSpecification::setDisplayWidth(int width) {
  if (width < kDefaultDisplayWidth) {
    throw InvalidArgumentException("Display width must be >= 64");
  }
  display_width_ = width;
}


int MachineSpecification::getDisplayWidth() const {
  return display_width_;
}


void MachineSpecification::setDisplayHeight(int height) {
  if (height < kDefaultDisplayHeight) {
    throw InvalidArgumentException("Display height must be >= 32");
  }
  display_height_ = height;
}


int MachineSpecification::getDisplayHeight() const {
  return display_height_;
}


void MachineSpecification::setTimerFrequency(int freq) {
  if (freq < kDefaultTimerFrequency || freq > kMaxTimerFrequency) {
    throw InvalidArgumentException("Timer frequency must be >= 60 and <= 500");
  }
  timer_frequency_ = freq;
}


int MachineSpecification::getTimerFrequency() const {
  return timer_frequency_;
}


} // namespace chip8
