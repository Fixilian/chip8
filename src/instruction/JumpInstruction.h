#ifndef CHIP8_INSTRUCTION_JUMPINSTRUCTION_H
#define CHIP8_INSTRUCTION_JUMPINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 1nnn JP addr instruction.
 */
class JumpInstruction : public Instruction {
 public:
  JumpInstruction(word opcode);

  virtual ~JumpInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_JUMPINSTRUCTION_H
