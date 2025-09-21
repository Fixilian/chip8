#include "SetDelayTimerInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SetDelayTimerInstruction::SetDelayTimerInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SetDelayTimerInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.setDt(ctx.registers[x]);
}


string SetDelayTimerInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "DT = Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
