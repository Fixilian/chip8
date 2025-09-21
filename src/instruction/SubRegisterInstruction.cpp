#include "SubRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SubRegisterInstruction::SubRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SubRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[x] > ctx.registers[y]) {
    ctx.registers[kFlagRegister] = 1;
  } else {
    ctx.registers[kFlagRegister] = 0;
  }
  ctx.registers[x] -= ctx.registers[y];
}


string SubRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx -= Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y << '\n';
  return stream.str();
}


} // namespace chip8
