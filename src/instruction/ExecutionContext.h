#ifndef CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H
#define CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H

#include <vector>

#include "base/Aliases.h"
#include "base/Stack.h"
#include "graphics/Frame.h"
#include "memory/Ram.h"

namespace chip8 {

/**
 * Program execution context.
 */
class ExecutionContext {
 public:
  ExecutionContext(int stack_size, Ram& ram, int frame_w, int frame_h);

  ExecutionContext(const ExecutionContext&) = delete;
  ExecutionContext& operator=(const ExecutionContext&) = delete;
  ExecutionContext(ExecutionContext&&) = delete;
  ExecutionContext& operator=(ExecutionContext&&) = delete;

  std::vector<byte> registers; // v0 - vF registers
  const byte* pc; // program counter
  word i; // register I
  Ram& ram;
  Frame frame;
  Stack<word> stack;

  byte dt(); // delay timer register
  byte st(); // sound timer register

  void updateTimers();

 private:
  byte dt_;
  byte st_;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H
