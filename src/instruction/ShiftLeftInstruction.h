#ifndef CHIP8_INSTRUCTION_SHIFTLEFTINSTRUCTION_H
#define CHIP8_INSTRUCTION_SHIFTLEFTINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xyE SHL Vx instruction.
 */
class ShiftLeftInstruction : public Instruction {
 public:
  ShiftLeftInstruction(word opcode);

  virtual ~ShiftLeftInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SHIFTLEFTINSTRUCTION_H
