#ifndef CHIP8_INSTRUCTION_BITWISEANDINSTRUCTION_H
#define CHIP8_INSTRUCTION_BITWISEANDINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy2 AND Vx, Vy instruction.
 */
class BitwiseAndInstruction : public Instruction {
 public:
  BitwiseAndInstruction(word opcode);

  virtual ~BitwiseAndInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_BITWISEANDINSTRUCTION_H
