#include "AddIInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


AddIInstruction::AddIInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddIInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.i += ctx.registers[x];
}


string AddIInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "I += Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  return stream.str();
}


} // namespace chip8
