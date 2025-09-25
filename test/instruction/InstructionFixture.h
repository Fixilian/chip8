#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "base/Allocator.h"
#include "instruction/ExecutionContext.h"
#include "instruction/InstructionPtr.h"
#include "keyboard/KeyboardMonitor.h"
#include "memory/Memory.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


class InstructionTest : public testing::Test {
 public:
  static const int kInstructionMax = 32;
  InstructionTest()
      : allocator_(sizeof(Instruction), kInstructionMax)
  {}

 protected:
  Allocator allocator_;
  unique_ptr<KeyboardMonitor> keyboard;
  unique_ptr<Memory> mem;
  unique_ptr<ExecutionContext> ctx;
  vector<InstructionPtr> ins;

  template <typename T>
  void setupContext(
    vector<bool> pressed, 
    vector<chip8::byte> regs, 
    vector<word> opcodes) 
  {
    keyboard = createKeyboardMonitor(pressed);
    mem = createMemory();
    ctx = createContextWithRegisters(regs, *mem, *keyboard);
    fillInstructions<T>(opcodes);
  }

  template <typename T>
  void setupContext(vector<chip8::byte> regs, vector<word> opcodes) {
    keyboard = createKeyboardMonitor();
    mem = createMemory();
    ctx = createContextWithRegisters(regs, *mem, *keyboard);
    fillInstructions<T>(opcodes);
  }

  template <typename T>
  void setupContext(vector<word> opcodes) {
    keyboard = createKeyboardMonitor();
    mem = createMemory();
    ctx = createContext(*mem, *keyboard);
    fillInstructions<T>(opcodes);
  }

  void setupContext() {
    keyboard = createKeyboardMonitor();
    mem = createMemory();
    ctx = createContext(*mem, *keyboard);
  }

  void setupContextWithFrame(int w, int h) {
    keyboard = createKeyboardMonitor();
    mem = createMemory();
    ctx = createContext(w, h, *mem, *keyboard);
  }

  void setupContextWithMemory(int size, int reserve) {
    keyboard = createKeyboardMonitor();
    mem = createMemory(size, reserve);
    ctx = createContext(*mem, *keyboard);
  }

  template <typename T>
  void setupContextWithMemory(
    int size, 
    int reserve, 
    vector<chip8::byte> regs, 
    vector<word> opcodes) 
  {
    keyboard = createKeyboardMonitor();
    mem = createMemory(size, reserve);
    ctx = createContextWithRegisters(regs, *mem, *keyboard);
    fillInstructions<T>(opcodes);
  }

  void setupContextWithMemory(int size, int reserve, vector<chip8::byte> regs) {
    keyboard = createKeyboardMonitor();
    mem = createMemory(size, reserve);
    ctx = createContextWithRegisters(regs, *mem, *keyboard);
  }

 private: 
  template <typename T>
  void fillInstructions(vector<word> opcodes) {
    ins.reserve(opcodes.size());
    for (size_t i = 0; i < opcodes.size(); i += 1) {
      ins.emplace_back(InstructionPtr::create<T>(opcodes[i], allocator_));
    }
  }
};
