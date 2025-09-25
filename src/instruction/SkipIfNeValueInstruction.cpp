#include "SkipIfNeValueInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SkipIfNeValueInstruction::SkipIfNeValueInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNeValueInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  if (ctx.registers[x] != kk) {
    ctx.pc += kPcStep;
  }
}


string SkipIfNeValueInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  stream << "Skip if Vx!=kk [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " kk=" << kk;
  return stream.str();
}


} // namespace chip8
