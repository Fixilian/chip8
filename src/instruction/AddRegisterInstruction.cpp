#include "AddRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


AddRegisterInstruction::AddRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  unsigned int sum = ctx.registers[x] + ctx.registers[y];
  if (sum > kByteMax) {
    ctx.registers[kFlagRegister] = 1;
  } else {
    ctx.registers[kFlagRegister] = 0;
  }
  ctx.registers[x] += ctx.registers[y];
}


} // namespace chip8
