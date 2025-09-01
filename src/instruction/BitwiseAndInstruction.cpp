#include "BitwiseAndInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


BitwiseAndInstruction::BitwiseAndInstruction(word opcode) 
    : Instruction(opcode)
{}  


void BitwiseAndInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] &= ctx.registers[y];
}


} // namespace chip8
