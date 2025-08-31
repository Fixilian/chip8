#include "CallInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


CallInstruction::CallInstruction(word opcode) 
    : Instruction(opcode)
{}  


void CallInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  auto diff = reinterpret_cast<const byte*>(ctx.pc) - ctx.ram.mem();
  ctx.stack.push(static_cast<word>(diff));
  const byte* p = ctx.ram.mem() + addr;
  ctx.pc = reinterpret_cast<const word*>(p);
}


} // namespace chip8
