#include "ShiftRightInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


ShiftRightInstruction::ShiftRightInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ShiftRightInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte bit = leastSignificantBitOf(ctx.registers[x]);
  ctx.registers[kFlagRegister] = bit;
  ctx.registers[x] >>= 1;
}


} // namespace chip8
