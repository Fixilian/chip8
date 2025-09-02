#ifndef CHIP8_INSTRUCTION_SKIPIFNOTPRESSEDINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFNOTPRESSEDINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * ExA1 SKNP Vx instruction.
 */
class SkipIfNotPressedInstruction : public Instruction {
 public:
  SkipIfNotPressedInstruction(word opcode);

  virtual ~SkipIfNotPressedInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFNOTPRESSEDINSTRUCTION_H
