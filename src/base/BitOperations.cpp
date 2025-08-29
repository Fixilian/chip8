#include "BitOperations.h"

using namespace std;

namespace chip8 {


static word get4Bits(word op, size_t shift) {
  word val = op >> shift;
  return val & 0xF;
}


word highest4BitsOf(word op) {
  size_t shift = sizeof(word) * kBits - 4;
  return get4Bits(op, shift);
}


word lowest12BitsOf(word op) {
  return op & 0xFFF;
}


word lowest8BitsOf(word op) {
  return op & 0xFF;
}


word lowest4BitsOf(word op) {
  return op & 0xF;
}


word getXFrom(word op) {
  size_t shift = (sizeof(word) - 1) * kBits;
  return get4Bits(op, shift);
}


word getYFrom(word op) {
  size_t shift = 4;
  return get4Bits(op, shift);
}


} // namespace chip8
