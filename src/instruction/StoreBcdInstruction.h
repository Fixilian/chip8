#ifndef CHIP8_INSTRUCTION_STOREBCDINSTRUCTION_H
#define CHIP8_INSTRUCTION_STOREBCDINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx33 LD B, Vx instruction.
 */
class StoreBcdInstruction : public Instruction {
 public:
  StoreBcdInstruction(word opcode);

  virtual ~StoreBcdInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_STOREBCDINSTRUCTION_H
