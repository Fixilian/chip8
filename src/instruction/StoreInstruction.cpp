#include "StoreInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


StoreInstruction::StoreInstruction(word opcode) 
    : Instruction(opcode)
{}  


void StoreInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  for (word i = 0; i <= x; i += 1) {
    ctx.ram[ctx.i + i] = ctx.registers[i];
  }
}


string StoreInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Store V0-Vx [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  return stream.str();
}


} // namespace chip8
