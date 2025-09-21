#include "SetSoundTimerInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SetSoundTimerInstruction::SetSoundTimerInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SetSoundTimerInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.setSt(ctx.registers[x]);
}


string SetSoundTimerInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "ST = Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
