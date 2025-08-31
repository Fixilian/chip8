#include "ReturnInstruction.h"

namespace chip8 {


ReturnInstruction::ReturnInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ReturnInstruction::execute(ExecutionContext& ctx) {
  ctx.pc = ctx.ram.mem() + ctx.stack.pop();
}


} // namespace chip8
