#include "JumpInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


JumpInstruction::JumpInstruction(word opcode) 
    : Instruction(opcode)
{}  


void JumpInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  ctx.pc = ctx.ram.mem() + addr;
}


string JumpInstruction::toString() const {
  stringstream stream;
  word addr = lowest12BitsOf(opcode_);
  stream << "Jump addr [0x" << hex << opcode_ << "]" << dec;
  stream << " addr=" << addr;
  return stream.str();
}


} // namespace chip8
