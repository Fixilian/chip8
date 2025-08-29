#include "RomBuilder.h"

#include "exception/OutOfRangeException.h"

using namespace std;

namespace chip8 {


RomBuilder::RomBuilder(int size) 
    : size_(size),
      insert_index_(0),
      capacity_(size / sizeof(word))
{
  rom_ = new word[capacity_];
}


RomBuilder::~RomBuilder() {
  delete[] rom_;
  rom_ = nullptr;
}


void RomBuilder::push(word opcode) {
  if (insert_index_ >= capacity_) {
    throw OutOfRangeException("Not enough space for opcode");
  }

  rom_[insert_index_] = opcode;
  insert_index_ += 1;
}


Rom RomBuilder::build() {
  return Rom(rom_, insert_index_ * sizeof(word));
}


} // namespace chip8
