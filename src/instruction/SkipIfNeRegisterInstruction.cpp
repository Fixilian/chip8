#include "SkipIfNeRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SkipIfNeRegisterInstruction::SkipIfNeRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNeRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  if (ctx.registers[x] != ctx.registers[y]) {
    ctx.pc += kPcStep;
  }
}


string SkipIfNeRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Skip if Vx!=Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y << '\n';
  return stream.str();
}


} // namespace chip8
