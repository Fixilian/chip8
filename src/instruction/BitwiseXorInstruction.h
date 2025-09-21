#ifndef CHIP8_INSTRUCTION_BITWISEXORINSTRUCTION_H
#define CHIP8_INSTRUCTION_BITWISEXORINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 8xy3 XOR Vx, Vy instruction.
 */
class BitwiseXorInstruction : public Instruction {
 public:
  BitwiseXorInstruction(word opcode);

  virtual ~BitwiseXorInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_BITWISEXORINSTRUCTION_H
