#include "ReturnInstruction.h"

namespace chip8 {


ReturnInstruction::ReturnInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ReturnInstruction::execute(ExecutionContext& ctx) {
  const byte* p = ctx.ram.mem() + ctx.stack.pop();
  ctx.pc = reinterpret_cast<const word*>(p);
}


} // namespace chip8
