#ifndef CHIP8_INSTRUCTION_SETDELAYTIMERINSTRUCTION_H
#define CHIP8_INSTRUCTION_SETDELAYTIMERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx15 LD DT, Vx instruction.
 */
class SetDelayTimerInstruction : public Instruction {
 public:
  SetDelayTimerInstruction(word opcode);

  virtual ~SetDelayTimerInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SETDELAYTIMERINSTRUCTION_H
