#include "LoadDtInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


LoadDtInstruction::LoadDtInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadDtInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.registers[x] = ctx.dt();
}


} // namespace chip8
