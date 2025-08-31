#ifndef CHIP8_INSTRUCTION_BITWISEORINSTRUCTION_H
#define CHIP8_INSTRUCTION_BITWISEORINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy1 OR Vx, Vy instruction.
 */
class BitwiseOrInstruction : public Instruction {
 public:
  BitwiseOrInstruction(word opcode);

  virtual ~BitwiseOrInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_BITWISEORINSTRUCTION_H
