#include "SkipIfPressedInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SkipIfPressedInstruction::SkipIfPressedInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfPressedInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.registers[x];
  if (ctx.keyboard.pressed(key)) {
    ctx.pc += kPcStep;
  }
}


} // namespace chip8
