#include "ClearDisplayInstruction.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace chip8 {


ClearDisplayInstruction::ClearDisplayInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ClearDisplayInstruction::execute(ExecutionContext& ctx) {
  ctx.frame.clear();
  ctx.notifyFrameListeners();
}


string ClearDisplayInstruction::toString() const {
  stringstream stream;
  stream << "Clear [0x" << hex << opcode_ << "]" << '\n';
  return stream.str();
}



} // namespace chip8
