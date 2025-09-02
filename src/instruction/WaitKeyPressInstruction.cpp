#include "WaitKeyPressInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


WaitKeyPressInstruction::WaitKeyPressInstruction(word opcode) 
    : Instruction(opcode)
{}  


void WaitKeyPressInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.keyboard.waitKeyPress();
  ctx.registers[x] = key;
}


} // namespace chip8
