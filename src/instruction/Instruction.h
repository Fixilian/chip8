#ifndef CHIP8_INSTRUCTION_INSTRUCTION_H
#define CHIP8_INSTRUCTION_INSTRUCTION_H

#include "base/Aliases.h"
#include "ExecutionContext.h"

namespace chip8 {

/**
 * Instruction interface.
 */
class Instruction {
 public:
  Instruction(word opcode);

  virtual ~Instruction() {};

  virtual void execute(ExecutionContext& ctx) = 0;

 protected:
  word opcode_;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_INSTRUCTION_H
