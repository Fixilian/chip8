#ifndef CHIP8_INSTRUCTION_SETSOUNDTIMERINSTRUCTION_H
#define CHIP8_INSTRUCTION_SETSOUNDTIMERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx18 LD ST, Vx instruction.
 */
class SetSoundTimerInstruction : public Instruction {
 public:
  SetSoundTimerInstruction(word opcode);

  virtual ~SetSoundTimerInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SETSOUNDTIMERINSTRUCTION_H
