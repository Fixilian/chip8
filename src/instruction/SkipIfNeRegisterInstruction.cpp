#include "SkipIfNeRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SkipIfNeRegisterInstruction::SkipIfNeRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNeRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[x] != ctx.registers[y]) {
    ctx.pc += kPcStep;
  }
}


} // namespace chip8
