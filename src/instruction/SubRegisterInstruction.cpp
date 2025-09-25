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
  bool flag = ctx.registers[x] >= ctx.registers[y];
  ctx.registers[x] -= ctx.registers[y];
  ctx.registers[kFlagRegister] = flag;
}


string SubRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx -= Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
