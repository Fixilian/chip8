#ifndef CHIP8_BASE_ENDIAN_H
#define CHIP8_BASE_ENDIAN_H

#include <bit>
#include <cstdint>
#include <type_traits>

#include "exception/OutOfRangeException.h"

namespace chip8 {

enum class Endianness {
  LittleEndian,
  BigEndian,
};


constexpr bool isBigEndian() {
  return std::endian::native == std::endian::big;
}


constexpr Endianness getSystemEndianess() {
  if (isBigEndian()) {
    return Endianness::BigEndian;
  } else {
    return Endianness::LittleEndian;
  }
}


template<Endianness to, class T>
inline T byte_swap_to(T value);


template<typename T, std::size_t sz>
struct swap_bytes {
  inline T operator()(T val) {
    throw OutOfRangeException("Invalid data size for swap bytes");
  }
};


template<typename T>
struct swap_bytes<T, 1> {
  inline T operator()(T val) {
    return val;
  }
};


template<typename T>
struct swap_bytes<T, 2> {
  inline T operator()(T val) {
    return ((((val) >> 8) & 0xff) | (((val) & 0xff) << 8));
  }
};


template<typename T>
struct swap_bytes<T, 4> {
  inline T operator()(T val) {
    return ((((val) & 0xff000000) >> 24) |
            (((val) & 0x00ff0000) >>  8) |
            (((val) & 0x0000ff00) <<  8) |
            (((val) & 0x000000ff) << 24));
  }
};


template<typename T>
struct swap_bytes<T, 8> {
  inline T operator()(T val) {
    return ((((val) & 0xff00000000000000ull) >> 56) |
            (((val) & 0x00ff000000000000ull) >> 40) |
            (((val) & 0x0000ff0000000000ull) >> 24) |
            (((val) & 0x000000ff00000000ull) >> 8 ) |
            (((val) & 0x00000000ff000000ull) << 8 ) |
            (((val) & 0x0000000000ff0000ull) << 24) |
            (((val) & 0x000000000000ff00ull) << 40) |
            (((val) & 0x00000000000000ffull) << 56));
  }
};


template<Endianness from, Endianness to, class T>
struct do_byte_swap {
  inline T operator()(T value) {
    return swap_bytes<T, sizeof(T)>()(value);
  }
};

// specialisations when attempting to swap to the same endianess
template<class T> 
struct do_byte_swap<Endianness::LittleEndian, Endianness::LittleEndian, T> { 
  inline T operator()(T value) { 
    return value; 
  } 
};


template<class T> 
struct do_byte_swap<Endianness::BigEndian, Endianness::BigEndian, T> {
  inline T operator()(T value) { 
    return value; 
  } 
};


template<Endianness to, class T>
inline T byte_swap_to(T value) {
  // ensure the data is only 1, 2, 4 or 8 bytes
  static_assert(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);
  // ensure we're only swapping arithmetic types
  static_assert(std::is_arithmetic<T>::value);

  constexpr auto system_endianess = getSystemEndianess();

  return do_byte_swap<system_endianess, to, T>()(value);
}

} // namespace chip8

#endif // CHIP8_BASE_ENDIAN_H
