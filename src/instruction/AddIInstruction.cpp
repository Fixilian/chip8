#include "AddIInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


AddIInstruction::AddIInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddIInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.i += ctx.registers[x];
}


} // namespace chip8
