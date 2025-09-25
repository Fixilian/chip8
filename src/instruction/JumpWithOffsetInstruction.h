#ifndef CHIP8_INSTRUCTION_JUMPWITHOFFSETINSTRUCTION_H
#define CHIP8_INSTRUCTION_JUMPWITHOFFSETINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Bnnn JP V0, addr instruction.
 */
class JumpWithOffsetInstruction : public Instruction {
 public:
  JumpWithOffsetInstruction(word opcode);

  virtual ~JumpWithOffsetInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_JUMPWITHOFFSETINSTRUCTION_H
