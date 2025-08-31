#ifndef CHIP8_INSTRUCTION_ADDVALUEINSTRUCTION_H
#define CHIP8_INSTRUCTION_ADDVALUEINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 7xkk ADD Vx, byte instruction.
 */
class AddValueInstruction : Instruction {
 public:
  AddValueInstruction(word opcode);

  virtual ~AddValueInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_ADDVALUEINSTRUCTION_H
