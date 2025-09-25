#include "LoadRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


LoadRegisterInstruction::LoadRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  ctx.registers[x] = ctx.registers[y];
}


string LoadRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx = Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
