#ifndef CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H
#define CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H

#include <atomic>
#include <vector>

#include "base/Aliases.h"
#include "base/Spinlock.h"
#include "base/Stack.h"
#include "graphics/Frame.h"
#include "graphics/FrameListener.h"
#include "keyboard/KeyboardMonitor.h"
#include "memory/Ram.h"

namespace chip8 {

constexpr int kPcStep = 2; // programm counter step

constexpr int kFlagRegister = 0xF; // flag register

/**
 * Program execution context.
 */
class ExecutionContext {
 public:
  ExecutionContext(
    int stack_size, 
    int frame_w, 
    int frame_h, 
    Ram& ram, 
    KeyboardMonitor& keyboard);

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
  KeyboardMonitor& keyboard;

  byte dt(); // delay timer register
  void setDt(byte val);

  byte st(); // sound timer register
  void setSt(byte val);

  void updateTimers();

  void addFrameListener(FrameListener& listener);

  void notifyFrameListeners();

 private:
  std::atomic<byte> dt_;
  std::atomic<byte> st_;
  Spinlock spin;
  std::vector<FrameListener*> frame_listeners_;
};

} // namespace chip8

#endif // CHIP8_INSTRUCTION_EXECUTIONCONTEXT_H
