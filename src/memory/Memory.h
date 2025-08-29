#ifndef CHIP8_MEMORY_MEMORY_H
#define CHIP8_MEMORY_MEMORY_H

#include "base/Aliases.h"
#include "base/Rom.h"

namespace chip8 {

constexpr int kDigitSpriteSize = 5; // sprite is 5 byte long.

/**
 * Memory interface.
 */
class Memory {
 public:
  virtual ~Memory() {}

  /**
   * Loads ROM into memory.
   */
  virtual void load(const Rom& rom) = 0;

  /**
   * Returns ROM begin pointer. 
   * @returns ROM begin pointer.
   */
  virtual const word* getRomBegin() = 0;

  /**
   * Returns ROM end pointer. 
   * @returns ROM end pointer.
   */
  virtual const word* getRomEnd() = 0;

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
};

} // namespace chip8

#endif // CHIP8_MEMORY_MEMORY_H
