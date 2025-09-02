#ifndef CHIP8_INSTRUCTION_TESTBASE_H
#define CHIP8_INSTRUCTION_TESTBASE_H

#include <memory>
#include <vector>

#include "instruction/ExecutionContext.h"
#include "instruction/Instruction.h"
#include "keyboard/KeyboardMonitor.h"
#include "memory/Memory.h"

namespace chip8 {

template <typename T>
std::vector<std::unique_ptr<Instruction>> 
generateInstructions(std::vector<word> opcodes);

std::unique_ptr<Memory> generateMemory();

std::unique_ptr<KeyboardMonitor> generateKeyboardMonitor();

std::unique_ptr<KeyboardMonitor> generateKeyboardMonitor(
  std::vector<bool> pressed);

std::unique_ptr<ExecutionContext> generateContext(
  Memory& mem, 
  KeyboardMonitor& keyboard);

std::unique_ptr<ExecutionContext> generateContext(
  int w, 
  int h, 
  Memory& mem, 
  KeyboardMonitor& keyboard);

std::unique_ptr<ExecutionContext> generateContextWithRegisters(
  std::vector<byte> regs, 
  Memory& mem, 
  KeyboardMonitor& keyboard);


template <typename T>
std::vector<std::unique_ptr<Instruction>> 
generateInstructions(std::vector<word> opcodes) {
  std::vector<std::unique_ptr<Instruction>> ins(opcodes.size());
  for (size_t i = 0; i < opcodes.size(); i += 1) {
    ins[i] = std::make_unique<T>(opcodes[i]);
  }
  return ins;
}


} // namespace chip8

#endif // CHIP8_INSTRUCTION_TESTBASE_H
