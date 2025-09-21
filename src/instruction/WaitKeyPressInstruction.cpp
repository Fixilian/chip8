#include "WaitKeyPressInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


WaitKeyPressInstruction::WaitKeyPressInstruction(word opcode) 
    : Instruction(opcode)
{}  


void WaitKeyPressInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.keyboard.waitKeyPress();
  ctx.registers[x] = key;
}


string WaitKeyPressInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Wait Vx = key [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
