#ifndef CHIP8_INSTRUCTION_SKIPIFNEVALUEINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFNEVALUEINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * 4xkk SNE Vx, byte instruction.
 */
class SkipIfNeValueInstruction : public Instruction {
 public:
  SkipIfNeValueInstruction(word opcode);

  virtual ~SkipIfNeValueInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFNEVALUEINSTRUCTION_H
