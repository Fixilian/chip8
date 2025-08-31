#ifndef CHIP8_INSTRUCTION_LOADVALUEINSTRUCTION_H
#define CHIP8_INSTRUCTION_LOADVALUEINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 6xkk LD Vx, byte instruction.
 */
class LoadValueInstruction : public Instruction {
 public:
  LoadValueInstruction(word opcode);

  virtual ~LoadValueInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_LOADVALUEINSTRUCTION_H
