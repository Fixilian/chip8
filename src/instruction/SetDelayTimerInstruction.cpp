#include "SetDelayTimerInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SetDelayTimerInstruction::SetDelayTimerInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SetDelayTimerInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.setDt(ctx.registers[x]);
}


} // namespace chip8
