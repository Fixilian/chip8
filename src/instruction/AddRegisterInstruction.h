#ifndef CHIP8_INSTRUCTION_ADDREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_ADDREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy4 ADD Vx, Vy instruction.
 */
class AddRegisterInstruction : public Instruction {
 public:
  AddRegisterInstruction(word opcode);

  virtual ~AddRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_ADDREGISTERINSTRUCTION_H
