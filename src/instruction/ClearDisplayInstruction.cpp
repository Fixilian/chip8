#include "ClearDisplayInstruction.h"

namespace chip8 {


ClearDisplayInstruction::ClearDisplayInstruction(word opcode) 
    : Instruction(opcode)
{}  


void ClearDisplayInstruction::execute(ExecutionContext& ctx) {
  ctx.frame.clear();
  ctx.notifyFrameListeners();
}


} // namespace chip8
