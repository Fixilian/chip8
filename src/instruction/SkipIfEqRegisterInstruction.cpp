#include "SkipIfEqRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SkipIfEqRegisterInstruction::SkipIfEqRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfEqRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[x] == ctx.registers[y]) {
    ctx.pc += kPcStep;
  }
}


} // namespace chip8
