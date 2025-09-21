#ifndef CHIP8_INSTRUCTION_LOADDTINSTRUCTION_H
#define CHIP8_INSTRUCTION_LOADDTINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx07 LD Vx, DT instruction.
 */
class LoadDtInstruction : public Instruction {
 public:
  LoadDtInstruction(word opcode);

  virtual ~LoadDtInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_LOADDTINSTRUCTION_H
