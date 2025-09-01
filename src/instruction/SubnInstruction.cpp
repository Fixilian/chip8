#include "SubnInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SubnInstruction::SubnInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SubnInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[y] > ctx.registers[x]) {
    ctx.registers[kFlagRegister] = 1;
  } else {
    ctx.registers[kFlagRegister] = 0;
  }
  ctx.registers[x] = ctx.registers[y] - ctx.registers[x];
}


} // namespace chip8
