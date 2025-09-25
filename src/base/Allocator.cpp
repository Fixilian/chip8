#include "Allocator.h"

#include "exception/SegFaultException.h"

namespace chip8 {


Allocator::Allocator(int block_size, int block_count)
    : block_size_(block_size), 
      block_count_(block_count),
      pool_index_(0),
      free_blocks_head_(nullptr)
{
  pool_ = new unsigned char[block_size_ * block_count_];
}


Allocator::~Allocator() {
  delete[] pool_;
  pool_ = nullptr;
}


void* Allocator::allocate() {
  void* free_block = pop();
  if (!free_block) { // If can't obtain existing block then get a new one
    if (pool_index_ < block_count_) {
      auto mem = pool_ + (pool_index_ * block_size_);
      pool_index_ += 1;
      free_block = reinterpret_cast<void*>(mem);
    } else {
      throw SegFaultException("Out of memory");
    }
  }
  return free_block;
}


void Allocator::deallocate(void* block) {
  if (block == nullptr) {
    return;
  }
  push(block);
}


void Allocator::push(void* ptr) {
  Block* block = reinterpret_cast<Block*>(ptr);
  block->next = free_blocks_head_;
  free_blocks_head_ = block;
}


void* Allocator::pop() {
  Block* block = nullptr;
  if (free_blocks_head_) {
    block = free_blocks_head_;
    free_blocks_head_ = free_blocks_head_->next;
  }
  void* ptr = reinterpret_cast<void*>(block);
  return ptr;
}


} // namespace chip8
