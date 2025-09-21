#include "SkipIfNotPressedInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


SkipIfNotPressedInstruction::SkipIfNotPressedInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SkipIfNotPressedInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte key = ctx.registers[x];
  if (!ctx.keyboard.pressed(key)) {
    ctx.pc += kPcStep;
  }
}


string SkipIfNotPressedInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Skip if not pressed x [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
