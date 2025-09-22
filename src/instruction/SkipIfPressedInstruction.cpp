#include "SkipIfPressedInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SkipIfPressedInstruction::SkipIfPressedInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfPressedInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.registers[x];
  if (ctx.keyboard.pressed(key)) {
    ctx.pc += kPcStep;
  }
}


string SkipIfPressedInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Skip if not x [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  return stream.str();
}


} // namespace chip8
