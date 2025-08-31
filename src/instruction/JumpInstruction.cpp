#include "JumpInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


JumpInstruction::JumpInstruction(word opcode) 
    : Instruction(opcode)
{}  


void JumpInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  ctx.pc = ctx.ram.mem() + addr;
}


} // namespace chip8
