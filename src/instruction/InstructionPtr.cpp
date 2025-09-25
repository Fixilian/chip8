#include "InstructionPtr.h"

using namespace std;

namespace chip8 {


InstructionPtr::~InstructionPtr() {
  allocator_.deallocate(ptr_);
  ptr_ = nullptr;
}


InstructionPtr::InstructionPtr(InstructionPtr&& other)
    : allocator_(other.allocator_)    
{
  ptr_ = other.ptr_;
  other.ptr_ = nullptr;
}


InstructionPtr& InstructionPtr::operator=(InstructionPtr&& other) {
  this->~InstructionPtr();
  new (this) InstructionPtr(std::move(other));
  return *this;
}


Instruction& InstructionPtr::operator*() {
  return *ptr_;
}


Instruction* InstructionPtr::operator->() {
  return ptr_;
}


Instruction* InstructionPtr::get() {
  return ptr_;
}


InstructionPtr::InstructionPtr(Allocator& allocator) 
    : allocator_(allocator),
      ptr_(nullptr)
{}


} // namespace chip8
