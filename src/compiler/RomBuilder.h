#ifndef CHIP8_COMPILER_ROMBUILDER_H
#define CHIP8_COMPILER_ROMBUILDER_H

#include <memory>

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
  RomBuilder(std::size_t size);
  
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
  std::size_t size_;
  std::size_t insert_index_;
  std::size_t capacity_;
  word* rom_;
};

} // namespace chip8

#endif // CHIP8_COMPILER_ROMBUILDER_H
