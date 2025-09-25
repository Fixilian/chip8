#ifndef CHIP8_INSTRUCTION_SKIPIFPRESSEDINSTRUCTION_H
#define CHIP8_INSTRUCTION_SKIPIFPRESSEDINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Ex9E SKP Vx instruction.
 */
class SkipIfPressedInstruction : public Instruction {
 public:
  SkipIfPressedInstruction(word opcode);

  virtual ~SkipIfPressedInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;

  virtual std::string toString() const override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_SKIPIFPRESSEDINSTRUCTION_H
