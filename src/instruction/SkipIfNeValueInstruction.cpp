#include "SkipIfNeValueInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SkipIfNeValueInstruction::SkipIfNeValueInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNeValueInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  if (ctx.registers[x] != kk) {
    ctx.pc += kPcStep;
  }
}


} // namespace chip8
