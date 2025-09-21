#ifndef CHIP8_INSTRUCTION_CALLINSTRUCTION_H
#define CHIP8_INSTRUCTION_CALLINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 2nnn CALL addr instruction.
 */
class CallInstruction : public Instruction {
 public:
  CallInstruction(word opcode);

  virtual ~CallInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_CALLINSTRUCTION_H
