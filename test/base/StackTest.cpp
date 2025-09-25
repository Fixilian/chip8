#include <gtest/gtest.h>

#include <vector>

#include "base/Stack.h"
#include "exception/OutOfRangeException.h"

using namespace std;
using namespace chip8;


TEST(StackTest, PushPop) {
  // Arrange
  int input_size = 5;
  vector<int> input = { 1, 2, 3, 4, 5 };
  vector<int> expected = { 5, 4, 3, 2, 1 };
  Stack<int> stack(input_size);

  // Act
  for (auto x : input) {
    stack.push(x);
  }

  // Assert
  for (int i = 0; i < stack.size(); i += 1) {
    int val = stack.pop();
    EXPECT_EQ(val, expected[i]);
  }
}


TEST(StackTest, ConstIterator) {
  // Arrange
  vector<int> input = { 1, 2, 3, 4, 5 };
  vector<int> expected = { 5, 4, 3, 2, 1 };
  vector<int> actual;
  int n = static_cast<int>(input.size());
  Stack<int> stack(n);
  for (auto x : input) {
    stack.push(x);
  }

  // Act
  for (const auto x : stack) {
    actual.push_back(x);
  }

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(StackTest, PopFromEmptyStack) {
  // Arrange
  int size = 5;
  Stack<int> stack(size);

  // Assert
  EXPECT_TRUE(stack.empty());
  EXPECT_THROW( { 
    stack.pop();
  }, OutOfRangeException);
}


TEST(StackTest, PushToFullStack) {
  // Arrange
  int input_size = 5;
  vector<int> input = { 1, 2, 3, 4, 5 };
  Stack<int> stack(input_size - 1);

  // Assert
  EXPECT_THROW( { 
    for (auto x : input) {
      stack.push(x);
    }
  }, OutOfRangeException);
}
