#include "InstructionTestBase.h"

#include "keyboard/HexKeyboardMonitor.h"
#include "memory/FixedMemory.h"

using namespace std;

namespace chip8 {


unique_ptr<Memory> generateMemory() {
  int mem_size = 1024;
  int mem_reserve = 512;
  return make_unique<FixedMemory>(mem_size, mem_reserve);
}


unique_ptr<KeyboardMonitor> generateKeyboardMonitor() {
  return make_unique<HexKeyboardMonitor>();
}


unique_ptr<ExecutionContext> generateContext(
  Memory& mem, 
  KeyboardMonitor& keyboard) 
{
  int w = 16;
  int h = 5;
  int stack_size = 16;
  return make_unique<ExecutionContext>(stack_size, w, h, mem, keyboard);
}


unique_ptr<ExecutionContext> generateContext(
  int w, 
  int h, 
  Memory& mem, 
  KeyboardMonitor& keyboard) 
{
  int stack_size = 16;
  return make_unique<ExecutionContext>(stack_size, w, h, mem, keyboard);
}


unique_ptr<ExecutionContext> generateContextWithRegisters(
  vector<byte> regs, 
  Memory& mem, 
  KeyboardMonitor& keyboard) 
{
  auto ctx = generateContext(mem, keyboard);
  for (size_t i = 0; i < regs.size(); i += 1) {
    ctx->registers[i] = regs[i];
  }
  ctx->pc = mem.getUserSpaceBegin();
  return ctx;
}


} // namespace chip8
