#ifndef CHIP8_INSTRUCTION_DRAWINSTRUCTION_H
#define CHIP8_INSTRUCTION_DRAWINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Dxyn DRW Vx, Vy, nibble instruction.
 */
class DrawInstruction : public Instruction {
 public:
  DrawInstruction(word opcode);

  virtual ~DrawInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_DRAWINSTRUCTION_H
