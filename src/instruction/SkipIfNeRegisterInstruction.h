#ifndef CHIP8_INSTRUCTION_SKIPIFNEREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFNEREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 9xy0 SNE Vx, Vy instruction.
 */
class SkipIfNeRegisterInstruction : public Instruction {
 public:
  SkipIfNeRegisterInstruction(word opcode);

  virtual ~SkipIfNeRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFNEREGISTERINSTRUCTION_H
