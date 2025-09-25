#include "SubnInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SubnInstruction::SubnInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SubnInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  bool flag = ctx.registers[y] >= ctx.registers[x];
  ctx.registers[x] = ctx.registers[y] - ctx.registers[x];
  ctx.registers[kFlagRegister] = flag;
}


string SubnInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx = Vy - Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
