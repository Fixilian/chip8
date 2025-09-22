#include "Rom.h"

#include <cstring>

using namespace std;

namespace chip8 {


Rom::Rom(const word* opcodes, int size)
    : size_(size)
{
  opcodes_ = new byte[size_];
  memcpy(opcodes_, opcodes, size_);
}


Rom::Rom(const byte* bytes, int size)
    : size_(size)
{
  opcodes_ = new byte[size_];
  memcpy(opcodes_, bytes, size_);
}


Rom::~Rom() {
  delete[] opcodes_;
  opcodes_ = nullptr;
}


Rom::Rom(const Rom& other) 
    : size_(other.size_)
{
  opcodes_ = new byte[size_];
  memcpy(opcodes_, other.opcodes_, size_);
}


Rom& Rom::operator=(const Rom& other) {
  this->~Rom();
  size_ = other.size_;

  opcodes_ = new byte[size_];
  memcpy(opcodes_, other.opcodes_, size_);
  
  return *this;
}


Rom::Rom(Rom&& other) 
    : size_(other.size_) 
{
  opcodes_ = other.opcodes_;
  other.opcodes_ = nullptr;
}


Rom& Rom::operator=(Rom&& other) {
  this->~Rom();
  size_ = other.size_;

  opcodes_ = other.opcodes_;
  other.opcodes_ = nullptr;

  return *this;
}


const byte* Rom::raw() const {
  return opcodes_;
}


const word* Rom::opcodes() const {
  return reinterpret_cast<const word*>(opcodes_);
}


int Rom::size() const {
  return size_;
}


} // namespace chip8
