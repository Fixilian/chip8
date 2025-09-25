#ifndef CHIP8_INSTRUCTION_SHIFTRIGHTINSTRUCTION_H
#define CHIP8_INSTRUCTION_SHIFTRIGHTINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy6 SHR Vx instruction.
 */
class ShiftRightInstruction : public Instruction {
 public:
  ShiftRightInstruction(word opcode);

  virtual ~ShiftRightInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SHIFTRIGHTINSTRUCTION_H
