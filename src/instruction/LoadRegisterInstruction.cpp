#include "LoadRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


LoadRegisterInstruction::LoadRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] = ctx.registers[y];
}


} // namespace chip8
