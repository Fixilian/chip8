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
  byte bit = leastSignificantBitOf(ctx.registers[x]);
  ctx.registers[x] >>= 1;
  ctx.registers[kFlagRegister] = bit;
}


string ShiftRightInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Vx >>= 1 [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  return stream.str();
}


} // namespace chip8
