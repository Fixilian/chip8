#include "LoadValueInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


LoadValueInstruction::LoadValueInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadValueInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  ctx.registers[x] = static_cast<byte>(kk);
}


} // namespace chip8
