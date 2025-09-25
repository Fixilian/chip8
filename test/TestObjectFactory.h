#ifndef CHIP8_TESTOBJECTFACTORY_H
#define CHIP8_TESTOBJECTFACTORY_H

#include <memory>
#include <vector>

#include "instruction/ExecutionContext.h"
#include "keyboard/KeyboardMonitor.h"
#include "memory/Memory.h"

namespace chip8 {

std::unique_ptr<Memory> createMemory();
std::unique_ptr<Memory> createMemory(int size, int reserve);

std::unique_ptr<Memory> createMemoryWithRom(const word* rom, int size);

std::unique_ptr<KeyboardMonitor> createKeyboardMonitor();
std::unique_ptr<KeyboardMonitor> createKeyboardMonitor(
  std::vector<bool> pressed);

std::unique_ptr<ExecutionContext> createContext(
  Memory& mem, 
  KeyboardMonitor& keyboard);
std::unique_ptr<ExecutionContext> createContext(
  int w, 
  int h, 
  Memory& mem, 
  KeyboardMonitor& keyboard);

std::unique_ptr<ExecutionContext> createContextWithRegisters(
  std::vector<byte> regs, 
  Memory& mem, 
  KeyboardMonitor& keyboard);


} // namespace chip8

#endif // CHIP8_TESTOBJECTFACTORY_H
