#include "BitwiseXorInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


BitwiseXorInstruction::BitwiseXorInstruction(word opcode) 
    : Instruction(opcode)
{}  


void BitwiseXorInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] ^= ctx.registers[y];
}


} // namespace chip8
