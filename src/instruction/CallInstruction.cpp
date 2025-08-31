#include "CallInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


CallInstruction::CallInstruction(word opcode) 
    : Instruction(opcode)
{}  


void CallInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  auto diff = ctx.pc - ctx.ram.mem();
  ctx.stack.push(static_cast<word>(diff));
  ctx.pc = ctx.ram.mem() + addr;
}


} // namespace chip8
