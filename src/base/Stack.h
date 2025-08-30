#ifndef CHIP8_BASE_STACK_H
#define CHIP8_BASE_STACK_H

#include <vector>

#include "exception/OutOfRangeException.h"

namespace chip8 {

template <typename T>
class Stack {
 public:
  Stack(int size);

  Stack(const Stack&) = default;
  Stack& operator=(const Stack&) = default;
  Stack(Stack&&) = default;
  Stack& operator=(Stack&&) = default;

  /**
   * Pushes value to stack.
   * @throws OutOfRangeException when trying to push to full stack.
   */
  void push(T val);

  /**
   * Returns top value from stack and deletes it.
   * @returns top value from stack.
   * @throws OutOfRangeException when trying to pop from empty stack.
   */
  T pop();

  /**
   * Returns true when stack is empty.
   * @return true when stack is empty.
   */
  bool empty() const;

  int size() const;

 private:
  int size_;
  int cur_;
  std::vector<T> values_;
};


template <typename T>
Stack<T>::Stack(int size)
    : size_(size),
      cur_(0),
      values_(size)
{}


template <typename T>
void Stack<T>::push(T val) {
  if (cur_ == size_) {
    throw OutOfRangeException("Attempt to push to full stack");
  }
  values_[cur_] = val;
  cur_ += 1;
}


template <typename T>
T Stack<T>::pop() {
  if (cur_ == 0) {
    throw OutOfRangeException("Attempt to pop from empty stack");
  }
  cur_ -= 1;
  return values_[cur_];
}


template <typename T>
bool Stack<T>::empty() const {
  return cur_ == 0;
}


template <typename T>
int Stack<T>::size() const {
  return size_;
}


} // namespace chip8

#endif // CHIP8_BASE_STACK_H
