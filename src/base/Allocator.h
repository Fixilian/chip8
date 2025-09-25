#ifndef CHIP8_BASE_ALLOCATOR_H
#define CHIP8_BASE_ALLOCATOR_H

namespace chip8 {

class Allocator {
 public:
  /**
   * @param block_size - size of the fixed blocks, min size = sizeof(pointer).
   * @param blocks_count - number of blocks in the pool.
   */
  Allocator(int block_size, int block_count);

  ~Allocator();

  Allocator(const Allocator&) = delete;
  Allocator& operator=(const Allocator&) = delete;
  Allocator(Allocator&&) = delete;
  Allocator& operator=(Allocator&&) = delete;

  /**
   * Returns pointer to the block.
   * @returns pointer to the block.
   * @throws SegFaultException when there is no free blocks.
   */
  void* allocate();

  /**
   * Returns a pointer to the memory pool.
   */
  void deallocate(void* block);

 private:
  struct Block {
    Block* next;
  };

  int block_size_;
  int block_count_;
  int pool_index_;
  Block* free_blocks_head_;
  unsigned char* pool_;

  /**
   * Push a memory block onto head of free-list.
   */
  void push(void* ptr);

  /**
   * Pop a memory block from head of free-list.
   */
  void* pop();
};

} // namespace chip8

#endif // CHIP8_BASE_ALLOCATOR_H
