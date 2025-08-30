#include "SysJumpInstruction.h"

namespace chip8 {


SysJumpInstruction::SysJumpInstruction(word opcode) 
    : Instruction(opcode)
{}  


void SysJumpInstruction::execute(ExecutionContext& ctx) {
  (void) ctx;
  // do nothing
}


} // namespace chip8
