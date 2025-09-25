#include "Spinlock.h"

using namespace std;

namespace chip8 {


Spinlock::Spinlock() {
  spin_.store(false, memory_order_release);
}


bool Spinlock::isLocked() const {
  return spin_.load(memory_order_relaxed);
}


bool Spinlock::tryLock() {
  bool cur = spin_.exchange(true, memory_order_acquire);
  return !cur;
}


void Spinlock::lock() {
  while (!tryLock()) {
    while (spin_.load(memory_order_acquire)) {
      // do noting
    }
  }
}


void Spinlock::unlock() {
  spin_.store(false, memory_order_release);
}


} // namespace chip8
