#include "Endian.h"

using namespace std;

namespace chip8 {


constexpr bool isBigEndian() {
  union {
    uint32_t i;
    char c[4];
  } u = {0x01020304};

  return u.c[0] == 1;
}


constexpr Endianness getSystemEndianess() {
  if (isBigEndian()) {
    return Endianness::BigEndian;
  } else {
    return Endianness::LittleEndian;
  }
}


} // namespace chip8
