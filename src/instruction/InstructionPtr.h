#ifndef CHIP8_INSTRUCTION_INSTRUCTIONPTR_H
#define CHIP8_INSTRUCTION_INSTRUCTIONPTR_H

#include "base/Aliases.h"
#include "base/Allocator.h"
#include "instruction/Instruction.h"

namespace chip8 {

/**
 * Instruction smart pointer.
 */
class InstructionPtr {
 public:
  ~InstructionPtr();

  InstructionPtr(const InstructionPtr&) = delete;
  InstructionPtr& operator=(const InstructionPtr&) = delete;
  InstructionPtr(InstructionPtr&&);
  InstructionPtr& operator=(InstructionPtr&&);

  Instruction& operator*();
  Instruction* operator->();

  Instruction* get();

  /**
   * @param allocator - instruction allocator, 
   * every instruction must fit in allocation block size.
   */
  template <typename T>
  static InstructionPtr create(word opcode, Allocator& allocator);
  
 private:
  Allocator& allocator_;
  Instruction* ptr_;

  InstructionPtr(Allocator& allocator);

  template <typename T> 
  void init(word opcode);
};


template <typename T>
InstructionPtr InstructionPtr::create(word opcode, Allocator& allocator) {
  InstructionPtr ptr(allocator);
  ptr.init<T>(opcode);
  return ptr;
}


template <typename T> 
void InstructionPtr::init(word opcode) {
  auto mem = allocator_.allocate();
  ptr_ = new (mem) T(opcode);
}


} // namespace chip8

#endif // CHIP8_INSTRUCTION_INSTRUCTIONPTR_H
