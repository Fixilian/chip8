#include "LoadValueInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


LoadValueInstruction::LoadValueInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadValueInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  ctx.registers[x] = static_cast<byte>(kk);
}


string LoadValueInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  stream << "Vx = kk [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " kk=" << kk;
  return stream.str();
}


} // namespace chip8
