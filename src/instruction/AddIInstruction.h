#ifndef CHIP8_INSTRUCTION_ADDIINSTRUCTION_H
#define CHIP8_INSTRUCTION_ADDIINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx1E ADD I, Vx instruction.
 */
class AddIInstruction : public Instruction {
 public:
  AddIInstruction(word opcode);

  virtual ~AddIInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_ADDIINSTRUCTION_H
