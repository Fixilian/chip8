#include "JumpInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


JumpInstruction::JumpInstruction(word opcode) 
    : Instruction(opcode)
{}  


void JumpInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  const byte* p = ctx.ram.mem() + addr;
  ctx.pc = reinterpret_cast<const word*>(p);
}


} // namespace chip8
