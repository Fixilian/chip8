#ifndef CHIP8_INSTRUCTION_LOADIREGISTERINSTRUCTION_H
#define CHIP8_INSTRUCTION_LOADIREGISTERINSTRUCTION_H

#include "Instruction.h"

namespace chip8 {

/**
 * Annn LD I instruction.
 */
class LoadIRegisterInstruction : public Instruction {
 public:
  LoadIRegisterInstruction(word opcode);

  virtual ~LoadIRegisterInstruction() {};

  virtual void execute(ExecutionContext& ctx) override;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_LOADIREGISTERINSTRUCTION_H
