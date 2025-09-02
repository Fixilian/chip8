#include "SetSoundTimerInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


SetSoundTimerInstruction::SetSoundTimerInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SetSoundTimerInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.setSt(ctx.registers[x]);
}


} // namespace chip8
