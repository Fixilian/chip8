#ifndef CHIP8_INSTRUCTION_GETSPRITELOCATIONINSTRUCTION_H
#define CHIP8_INSTRUCTION_GETSPRITELOCATIONINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx29 LD F, Vx instruction.
 */
class GetSpriteLocationInstruction : public Instruction {
 public:
  GetSpriteLocationInstruction(word opcode);

  virtual ~GetSpriteLocationInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_GETSPRITELOCATIONINSTRUCTION_H
