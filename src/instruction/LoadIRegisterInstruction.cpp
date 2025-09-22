#include "LoadIRegisterInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


LoadIRegisterInstruction::LoadIRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadIRegisterInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  ctx.i = addr;
}


string LoadIRegisterInstruction::toString() const {
  stringstream stream;
  word addr = lowest12BitsOf(opcode_);
  stream << "I = addr [0x" << hex << opcode_ << "]" << dec;
  stream << " addr=" << addr;
  return stream.str();
}


} // namespace chip8
