#include "ShiftLeftInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


ShiftLeftInstruction::ShiftLeftInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ShiftLeftInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte bit = mostSignificantBitOf(ctx.registers[x]);
  ctx.registers[kFlagRegister] = bit;
  ctx.registers[x] <<= 1;
}


} // namespace chip8
