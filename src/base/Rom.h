#ifndef CHIP8_BASE_ROM_H
#define CHIP8_BASE_ROM_H

#include "Aliases.h"

namespace chip8 {

/**
 * Binary ROM.
 */
class Rom {
 public:
  /**
   * Creates ROM from array of opcodes. 
   * @param opcodes - array of opcodes.
   * @param size - size in bytes.
   */
  Rom(const word* opcodes, int size);

  /**
   * Creates ROM from array of bytes. 
   * @param bytes - array of bytes.
   * @param size - size in bytes.
   */
  Rom(const byte* bytes, int size);

  ~Rom();

  Rom(const Rom&);
  Rom& operator=(const Rom&);
  Rom(Rom&&);
  Rom& operator=(Rom&&);

  const byte* raw() const;

  const word* opcodes() const;

  int size() const;

  void fixEndianess();

 private:
  byte* opcodes_;
  int size_;
};

} // namespace chip8

#endif // CHIP8_BASE_ROM_H
