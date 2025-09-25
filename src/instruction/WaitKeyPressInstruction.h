#ifndef CHIP8_INSTRUCTION_WAITKEYPRESSINSTRUCTION_H
#define CHIP8_INSTRUCTION_WAITKEYPRESSINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Fx0A LD Vx, K instruction.
 */
class WaitKeyPressInstruction : public Instruction {
 public:
  WaitKeyPressInstruction(word opcode);

  virtual ~WaitKeyPressInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_WAITKEYPRESSINSTRUCTION_H
