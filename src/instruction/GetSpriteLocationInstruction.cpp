#include "GetSpriteLocationInstruction.h"

#include "base/BitOperations.h"

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


} // namespace chip8
