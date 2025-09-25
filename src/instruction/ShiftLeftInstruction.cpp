#include "ShiftLeftInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


ShiftLeftInstruction::ShiftLeftInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ShiftLeftInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] = ctx.registers[y];
  byte bit = mostSignificantBitOf(ctx.registers[x]);
  ctx.registers[x] <<= 1;
  ctx.registers[kFlagRegister] = bit;
}


string ShiftLeftInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx = Vy << 1 [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
