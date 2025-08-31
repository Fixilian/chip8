#ifndef CHIP8_INSTRUCTION_SKIPIFEQVALUEINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFEQVALUEINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 3xkk SE Vx, byte instruction.
 */
class SkipIfEqValueInstruction : Instruction {
 public:
  SkipIfEqValueInstruction(word opcode);

  virtual ~SkipIfEqValueInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFEQVALUEINSTRUCTION_H
