#include "AddRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


AddRegisterInstruction::AddRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] += ctx.registers[y];
}


} // namespace chip8
