#include "EndOfProgramDetector.h"

#include "base/BitOperations.h"

namespace chip8 {


EndOfProgramDetector::EndOfProgramDetector(Memory& memory, ExecutionContext& ctx)
    : memory_(memory),
      ctx_(ctx),
      previous_pc_(ctx.pc)
{}


bool EndOfProgramDetector::endOfProgram(word opcode) {
  return endOfRom() || infiniteLoop(opcode) || isRetFromMain(opcode);
}


bool EndOfProgramDetector::endOfRom() {
  return ctx_.pc >= memory_.getRomEnd();
}


bool EndOfProgramDetector::infiniteLoop(word opcode) {
  word first_digit = highest4BitsOf(opcode);
  if (first_digit != 0x1) {
    return false;
  }
  word addr = lowest12BitsOf(opcode);
  word diff = static_cast<word>(ctx_.pc - memory_.mem());
  return addr == diff;
}


bool EndOfProgramDetector::isRetFromMain(word opcode) {
  const word ret_opcode = 0x00EE;
  return ctx_.stack.empty() && opcode == ret_opcode;
}


} // namespace chip8
