#ifndef CHIP8_COMPILER_ROMBUILDER_H
#define CHIP8_COMPILER_ROMBUILDER_H

#include "base/Aliases.h"
#include "base/Rom.h"

namespace chip8 {

/**
 * ROM builder.
 */
class RomBuilder {
 public:
  /**
   * Creates empty Rom.
   * @param size - rom size in bytes.
   */
  RomBuilder(int size);
  
  ~RomBuilder();

  RomBuilder(const RomBuilder&) = delete;
  RomBuilder& operator=(const RomBuilder&) = delete;
  RomBuilder(RomBuilder&&) = delete;
  RomBuilder& operator=(RomBuilder&&) = delete;

  /**
   * Inserts opcode to the end of ROM if insert allowed.
   * @throws OutOfRangeException if not enough space for opcode.
   */
  void push(word opcode);

  /**
   * Builds ROM.
   * @returns ROM.
   */
  Rom build();
 
 private:
  int size_;
  int insert_index_;
  int capacity_;
  word* rom_;
};

} // namespace chip8

#endif // CHIP8_COMPILER_ROMBUILDER_H
