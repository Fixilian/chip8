#ifndef CHIP8_EXECUTION_DECODER_H
#define CHIP8_EXECUTION_DECODER_H

#include "base/Aliases.h"
#include "instruction/InstructionPtr.h"

namespace chip8 {

/**
 * Opcode decoder.
 */
class Decoder {
 public:
  virtual ~Decoder() {}

  virtual InstructionPtr decode(word opcode) = 0;
};

} // namespace chip8

#endif // CHIP8_EXECUTION_DECODER_H
