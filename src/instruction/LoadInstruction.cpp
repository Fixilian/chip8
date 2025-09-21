#include "LoadInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


LoadInstruction::LoadInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  const auto& ram = ctx.ram;
  for (word i = 0; i <= x; i += 1) {
    ctx.registers[i] = ram[ctx.i + i];
  }
}


string LoadInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Load V0-Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
