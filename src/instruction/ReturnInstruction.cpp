#include "ReturnInstruction.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace chip8 {


ReturnInstruction::ReturnInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ReturnInstruction::execute(ExecutionContext& ctx) {
  ctx.pc = ctx.ram.mem() + ctx.stack.pop();
}


string ReturnInstruction::toString() const {
  stringstream stream;
  stream << "Ret [0x" << hex << opcode_ << "]";
  return stream.str();
}


} // namespace chip8
