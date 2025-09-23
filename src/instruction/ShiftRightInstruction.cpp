#include "ShiftRightInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


ShiftRightInstruction::ShiftRightInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ShiftRightInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] = ctx.registers[y];
  byte bit = leastSignificantBitOf(ctx.registers[x]);
  ctx.registers[x] >>= 1;
  ctx.registers[kFlagRegister] = bit;
}


string ShiftRightInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx = Vy >> 1 [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
