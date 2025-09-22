#include <gtest/gtest.h>

#include <vector>

#include "base/Allocator.h"
#include "exception/SegFaultException.h"

using namespace std;
using namespace chip8;


TEST(AllocatorTest, Alloc) {
  // Arrange
  vector<int> expected = { 0, 1, 2, 3, 4, 5, 6, 7 };
  vector<int*> actual(expected.size()); 
  int block_size = sizeof(long long);
  int block_count = static_cast<int>(expected.size());
  Allocator allocator(block_size, block_count);

  // Act
  for (int i = 0; i < block_count; i += 1) {
    auto mem = reinterpret_cast<int*>(allocator.allocate());
    actual[i] = mem;
    *mem = expected[i];
  }

  // Assert
  for (int i = 0; i < block_count; i += 1) {
    EXPECT_EQ(*(actual[i]), expected[i]);
    allocator.deallocate(actual[i]);
  }
}


TEST(AllocatorTest, SegFault) {
  // Arrange
  int block_size = sizeof(long long);
  int block_count = 2;
  Allocator allocator(block_size, block_count);
  
  // Assert
  EXPECT_THROW({
    for (int i = 0; i <= block_count; i += 1) {
      allocator.allocate();
    }
  }, SegFaultException);
}
