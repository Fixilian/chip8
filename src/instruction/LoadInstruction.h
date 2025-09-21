#ifndef CHIP8_INSTRUCTION_LOADINSTRUCTION_H
#define CHIP8_INSTRUCTION_LOADINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx65 LD Vx, [I] instruction.
 */
class LoadInstruction : public Instruction {
 public:
  LoadInstruction(word opcode);

  virtual ~LoadInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_LOADINSTRUCTION_H
