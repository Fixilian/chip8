#ifndef CHIP8_INSTRUCTION_SKIPIFEQREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFEQREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 5xy0 SE Vx, Vy instruction.
 */
class SkipIfEqRegisterInstruction : public Instruction {
 public:
  SkipIfEqRegisterInstruction(word opcode);

  virtual ~SkipIfEqRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFEQREGISTERINSTRUCTION_H
