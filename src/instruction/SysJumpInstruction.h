#ifndef CHIP8_INSTRUCTION_SYSJUMPINSTRUCTION_H
#define CHIP8_INSTRUCTION_SYSJUMPINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 0nnn SYS instruction.
 */
class SysJumpInstruction : public Instruction {
 public:
  SysJumpInstruction(word opcode);

  virtual ~SysJumpInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SYSJUMPINSTRUCTION_H
