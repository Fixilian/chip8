#include "CallInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


CallInstruction::CallInstruction(word opcode) 
    : Instruction(opcode)
{}  


void CallInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  auto diff = ctx.pc - ctx.ram.mem();
  ctx.stack.push(static_cast<word>(diff));
  ctx.pc = ctx.ram.mem() + addr;
}


string CallInstruction::toString() const {
  stringstream stream;
  word addr = lowest12BitsOf(opcode_);
  stream << "Call addr [0x" << hex << opcode_ << "]" << dec;
  stream << " addr=" << addr << '\n';
  return stream.str();
}


} // namespace chip8
