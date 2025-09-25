#include "GetSpriteLocationInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


GetSpriteLocationInstruction::GetSpriteLocationInstruction(word opcode) 
    : Instruction(opcode)
{}  


void GetSpriteLocationInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  int digit = ctx.registers[x];
  auto loc = ctx.ram.getDigitSprite(digit);
  ctx.i = static_cast<word>(loc - ctx.ram.mem());
}


string GetSpriteLocationInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  stream << "I = sprite[x] [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  return stream.str();
}


} // namespace chip8
