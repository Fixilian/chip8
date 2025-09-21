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
  byte bit = mostSignificantBitOf(ctx.registers[x]);
  ctx.registers[kFlagRegister] = bit;
  ctx.registers[x] <<= 1;
}


string ShiftLeftInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Vx <<= 1 [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
