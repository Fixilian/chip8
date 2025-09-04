#ifndef CHIP8_EMULATOR_CHIP8DECODER_H
#define CHIP8_EMULATOR_CHIP8DECODER_H

#include "base/Allocator.h"
#include "Decoder.h"

namespace chip8 {

/**
 * Chip8 opcode decoder.
 */
class Chip8Decoder : public Decoder {
 public:
  /**
   * @param allocator - instruction allocator, 
   * every instruction must fit in allocation block size.
   */
  Chip8Decoder(Allocator& allocator);

  virtual ~Chip8Decoder() {}

  virtual InstructionPtr decode(word opcode) override;

 private:
  Allocator& allocator_;

  InstructionPtr decode0nnn(word op);
  InstructionPtr decode5nnn(word op);
  InstructionPtr decode8nnn(word op);
  InstructionPtr decode9nnn(word op);
  InstructionPtr decodeEnnn(word op);
  InstructionPtr decodeFnnn(word op);

  template <typename T>
  InstructionPtr create(word op);
};


template <typename T>
InstructionPtr Chip8Decoder::create(word op) {
  return InstructionPtr::create<T>(op, allocator_);
}


} // namespace chip8

#endif // CHIP8_EMULATOR_CHIP8DECODER_H
