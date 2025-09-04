#ifndef CHIP8_EMULATOR_DECODER_H
#define CHIP8_EMULATOR_DECODER_H

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

#endif // CHIP8_EMULATOR_DECODER_H
