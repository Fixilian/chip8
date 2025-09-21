#include "RandomInstruction.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


RandomInstruction::RandomInstruction(word opcode) 
    : Instruction(opcode)
{}  


void RandomInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  srand(static_cast<unsigned int>(time({})));
  int r = rand() % kByteMax;
  ctx.registers[x] = static_cast<byte>(r & kk);
}


string RandomInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  stream << "Vx = rand & kk [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " kk=" << kk << '\n';
  return stream.str();
}


} // namespace chip8
