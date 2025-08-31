#include "AddValueInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


AddValueInstruction::AddValueInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddValueInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  ctx.registers[x] += static_cast<byte>(kk);
}


} // namespace chip8
