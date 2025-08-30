#ifndef CHIP8_MEMORY_RAM_H
#define CHIP8_MEMORY_RAM_H

#include "base/Aliases.h"

namespace chip8 {

constexpr int kDigitSpriteSize = 5; // sprite is 5 byte long.

/**
 * Random access memory interface.
 */
class Ram {
 public:
  virtual ~Ram() {}

  /**
   * @throws SegFaultException when trying to access read only memory.
   */
  virtual byte& operator[](int index) = 0;
  virtual const byte& operator[](int index) const = 0;

  /**
   * Returns digit sprite begin pointer. 
   * @returns digit sprite begin pointer.
   */
  virtual const byte* getDigitSprite(int digit) = 0;

  /**
   * Returns raw pointer to memory start.
   * @returns raw pointer to memory start.
   */
  virtual const byte* mem() const = 0;
};

} // namespace chip8

#endif // CHIP8_MEMORY_RAM_H
