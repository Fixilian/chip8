#ifndef CHIP8_INSTRUCTION_RETURNINSTRUCTION_H
#define CHIP8_INSTRUCTION_RETURNINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 00EE RET instruction.
 */
class ReturnInstruction : Instruction {
 public:
  ReturnInstruction(word opcode);

  virtual ~ReturnInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_RETURNINSTRUCTION_H
