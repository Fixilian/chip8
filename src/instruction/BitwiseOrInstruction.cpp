#include "BitwiseOrInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


BitwiseOrInstruction::BitwiseOrInstruction(word opcode) 
    : Instruction(opcode)
{}  


void BitwiseOrInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] |= ctx.registers[y];
}


} // namespace chip8
