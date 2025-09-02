#include "StoreBcdInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


StoreBcdInstruction::StoreBcdInstruction(word opcode) 
    : Instruction(opcode)
{}  


void StoreBcdInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte n = ctx.registers[x];
  writeBcdOf(n, ctx.ram[ctx.i], ctx.ram[ctx.i + 1], ctx.ram[ctx.i + 2]);
}


} // namespace chip8
