#include "InstructionTestBase.h"

#include "memory/FixedMemory.h"

using namespace std;

namespace chip8 {


unique_ptr<Memory> generateMemory() {
  int mem_size = 1024;
  int mem_reserve = 512;
  return make_unique<FixedMemory>(mem_size, mem_reserve);
}


unique_ptr<ExecutionContext> generateContext(Memory& mem) {
  int w = 16;
  int h = 5;
  int stack_size = 16;
  return make_unique<ExecutionContext>(stack_size, mem, w, h);
}


unique_ptr<ExecutionContext> generateContext(int w, int h, Memory& mem) {
  int stack_size = 16;
  return make_unique<ExecutionContext>(stack_size, mem, w, h);
}


unique_ptr<ExecutionContext> 
generateContextWithRegisters(vector<byte> regs, Memory& mem) {
  auto ctx = generateContext(mem);
  for (size_t i = 0; i < regs.size(); i += 1) {
    ctx->registers[i] = regs[i];
  }
  ctx->pc = mem.getUserSpaceBegin();
  return ctx;
}


} // namespace chip8
