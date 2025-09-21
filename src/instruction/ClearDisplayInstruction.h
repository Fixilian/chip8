#ifndef CHIP8_INSTRUCTION_CLEARDISPLAYINSTRUCTION_H
#define CHIP8_INSTRUCTION_CLEARDISPLAYINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 00E0 CLS instruction.
 */
class ClearDisplayInstruction : public Instruction {
 public:
  ClearDisplayInstruction(word opcode);

  virtual ~ClearDisplayInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_CLEARDISPLAYINSTRUCTION_H
