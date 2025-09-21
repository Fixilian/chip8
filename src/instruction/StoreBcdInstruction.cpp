#include "StoreBcdInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


StoreBcdInstruction::StoreBcdInstruction(word opcode) 
    : Instruction(opcode)
{}  


void StoreBcdInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  byte n = ctx.registers[x];
  writeBcdOf(n, ctx.ram[ctx.i], ctx.ram[ctx.i + 1], ctx.ram[ctx.i + 2]);
}


string StoreBcdInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "Store Vx BCD [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x << '\n';
  return stream.str();
}


} // namespace chip8
