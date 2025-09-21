#ifndef CHIP8_INSTRUCTION_SUBREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_SUBREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy5 SUB Vx, Vy instruction.
 */
class SubRegisterInstruction : public Instruction {
 public:
  SubRegisterInstruction(word opcode);

  virtual ~SubRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SUBREGISTERINSTRUCTION_H
