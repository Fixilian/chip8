#include "JumpWithOffsetInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


JumpWithOffsetInstruction::JumpWithOffsetInstruction(word opcode) 
    : Instruction(opcode)
{}  


void JumpWithOffsetInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  word offset = addr + ctx.registers[0];
  ctx.pc = ctx.ram.mem() + offset;
}


} // namespace chip8
