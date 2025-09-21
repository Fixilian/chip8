#include "LoadDtInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


LoadDtInstruction::LoadDtInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadDtInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  ctx.registers[x] = ctx.dt();
}


string LoadDtInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Vx = DT [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
