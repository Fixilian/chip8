#ifndef CHIP8_EXECUTION_ENDOFPROGRAMDETECTOR_H
#define CHIP8_EXECUTION_ENDOFPROGRAMDETECTOR_H

#include "base/Aliases.h"
#include "instruction/ExecutionContext.h"
#include "memory/Memory.h"

namespace chip8 {

/**
 * End of program detector.
 * 
 * It detects 3 situations:
 * 
 * Return from "main": RET instruction when call stack is empty.
 * 
 * Infinite loop: JP addr instruction where the target address 
 * is the instruction itself, creating a self-referencing loop.
 * 
 * End of ROM : reaching the end of the loaded ROM data.
 */
class EndOfProgramDetector {
 public:
  EndOfProgramDetector(Memory& memory, ExecutionContext& ctx);

  EndOfProgramDetector(const EndOfProgramDetector&) = delete;
  EndOfProgramDetector& operator=(const EndOfProgramDetector&) = delete;
  EndOfProgramDetector(EndOfProgramDetector&&) = delete;
  EndOfProgramDetector& operator=(EndOfProgramDetector&&) = delete;

  /**
   * @param opcode - opcode of instruction not yet executed.
   */
  bool endOfProgram(word opcode);

 private:
  Memory& memory_;
  ExecutionContext& ctx_;
  const byte* previous_pc_;

  bool endOfRom();
  bool infiniteLoop(word opcode);
  bool isRetFromMain(word opcode);
};

} // namespace chip8

#endif // CHIP8_EXECUTION_ENDOFPROGRAMDETECTOR_H
