#ifndef CHIP8_INSTRUCTION_LOADREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_LOADREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy0 LD Vx, Vy instruction.
 */
class LoadRegisterInstruction : Instruction {
 public:
  LoadRegisterInstruction(word opcode);

  virtual ~LoadRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_LOADREGISTERINSTRUCTION_H
