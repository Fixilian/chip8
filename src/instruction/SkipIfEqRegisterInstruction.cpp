#include "SkipIfEqRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SkipIfEqRegisterInstruction::SkipIfEqRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfEqRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[x] == ctx.registers[y]) {
    ctx.pc += kPcStep;
  }
}


string SkipIfEqRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Skip if Vx=Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
