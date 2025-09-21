#include "BitwiseAndInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


BitwiseAndInstruction::BitwiseAndInstruction(word opcode) 
    : Instruction(opcode)
{}  


void BitwiseAndInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] &= ctx.registers[y];
}


string BitwiseAndInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx &= kk [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y << '\n';
  return stream.str();
}


} // namespace chip8
