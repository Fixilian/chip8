#include "SysJumpInstruction.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace chip8 {


SysJumpInstruction::SysJumpInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SysJumpInstruction::execute(ExecutionContext& ctx) {
  (void) ctx;
  // do nothing
}


string SysJumpInstruction::toString() const {
  stringstream stream;
  stream << "Sys jump [0x" << hex << opcode_ << "]";
  return stream.str();
}


} // namespace chip8
