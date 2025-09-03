#ifndef CHIP8_INSTRUCTION_STOREINSTRUCTION_H
#define CHIP8_INSTRUCTION_STOREINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx55 LD [I], Vx instruction.
 */
class StoreInstruction : public Instruction {
 public:
  StoreInstruction(word opcode);

  virtual ~StoreInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_STOREINSTRUCTION_H
