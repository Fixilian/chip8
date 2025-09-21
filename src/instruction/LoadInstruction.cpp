#include "LoadInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


LoadInstruction::LoadInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  const auto& ram = ctx.ram;
  for (word i = 0; i <= x; i += 1) {
    ctx.registers[i] = ram[ctx.i + i];
  }
}


} // namespace chip8
