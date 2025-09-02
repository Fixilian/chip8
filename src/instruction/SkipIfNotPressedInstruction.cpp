#include "SkipIfNotPressedInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SkipIfNotPressedInstruction::SkipIfNotPressedInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNotPressedInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.registers[x];
  if (!ctx.keyboard.pressed(key)) {
    ctx.pc += kPcStep;
  }
}


} // namespace chip8
