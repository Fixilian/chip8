#include "JumpWithOffsetInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


JumpWithOffsetInstruction::JumpWithOffsetInstruction(word opcode) 
    : Instruction(opcode)
{}  


void JumpWithOffsetInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  word offset = addr + ctx.registers[0];
  ctx.pc = ctx.ram.mem() + offset;
}


string JumpWithOffsetInstruction::toString() const {
  stringstream stream;
  word addr = lowest12BitsOf(opcode_);
  stream << "Jump addr+V0 [0x" << hex << opcode_ << "]" << dec;
  stream << " addr=" << addr;
  return stream.str();
}


} // namespace chip8
