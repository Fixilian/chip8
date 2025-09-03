#include "StoreInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


StoreInstruction::StoreInstruction(word opcode) 
    : Instruction(opcode)
{}  


void StoreInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  for (word i = 0; i <= x; i += 1) {
    ctx.ram[ctx.i + i] = ctx.registers[i];
  }
}


} // namespace chip8
