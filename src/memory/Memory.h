#ifndef CHIP8_MEMORY_MEMORY_H
#define CHIP8_MEMORY_MEMORY_H

#include "base/Aliases.h"
#include "base/Rom.h"
#include "Ram.h"

namespace chip8 {

/**
 * Memory interface.
 */
class Memory : public Ram {
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
  virtual const byte* getRomBegin() = 0;

  /**
   * Returns ROM end pointer. 
   * @returns ROM end pointer.
   */
  virtual const byte* getRomEnd() = 0;
};

} // namespace chip8

#endif // CHIP8_MEMORY_MEMORY_H
