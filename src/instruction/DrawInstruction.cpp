#include "DrawInstruction.h"

#include <iostream>
#include <sstream>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


DrawInstruction::DrawInstruction(word opcode) 
    : Instruction(opcode)
{}  


void DrawInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  word nibble = lowest4BitsOf(opcode_);
  const byte* sprite = ctx.ram.mem() + ctx.i;
  byte x0 = ctx.registers[x];
  byte y0 = ctx.registers[y];
  ctx.frame.draw(sprite, nibble, x0, y0);
  ctx.notifyFrameListeners();
}


string DrawInstruction::toString() const {
  stringstream stream;
  word x = getXFrom(opcode_);
  word y = getYFrom(opcode_);
  word nibble = lowest4BitsOf(opcode_);
  stream << "Draw (Vx, Vy) [0x" << hex << opcode_ << "]" << dec;
  stream << " x=" << x;
  stream << " y=" << y;
  stream << " len=" << nibble << '\n';
  return stream.str();
}


} // namespace chip8
