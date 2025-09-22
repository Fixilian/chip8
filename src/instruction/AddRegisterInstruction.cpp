#include "AddRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


AddRegisterInstruction::AddRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void AddRegisterInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  unsigned int sum = ctx.registers[x] + ctx.registers[y];
  bool flag = sum > kByteMax;
  ctx.registers[x] += ctx.registers[y];
  ctx.registers[kFlagRegister] = flag;
}


string AddRegisterInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  stream << "Vx += Vy [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  return stream.str();
}


} // namespace chip8
