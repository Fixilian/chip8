#ifndef CHIP8_INSTRUCTION_SUBNINSTRUCTION_H
#define CHIP8_INSTRUCTION_SUBNINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy7 SUBN Vx, Vy instruction.
 */
class SubnInstruction : public Instruction {
 public:
  SubnInstruction(word opcode);

  virtual ~SubnInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SUBNINSTRUCTION_H
