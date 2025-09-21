#ifndef CHIP8_INSTRUCTION_RANDOMINSTRUCTION_H
#define CHIP8_INSTRUCTION_RANDOMINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Cxkk RND Vx, byte instruction.
 */
class RandomInstruction : public Instruction {
 public:
  RandomInstruction(word opcode);

  virtual ~RandomInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_RANDOMINSTRUCTION_H
