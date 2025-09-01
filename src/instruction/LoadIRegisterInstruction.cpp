#include "LoadIRegisterInstruction.h"

#include "base/BitOperations.h"

namespace chip8 {


LoadIRegisterInstruction::LoadIRegisterInstruction(word opcode) 
    : Instruction(opcode)
{}  


void LoadIRegisterInstruction::execute(ExecutionContext& ctx) {
  word addr = lowest12BitsOf(opcode_);
  ctx.i = addr;
}


} // namespace chip8
