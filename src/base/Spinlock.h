#ifndef CHIP8_BASE_SPINLOCK_H
#define CHIP8_BASE_SPINLOCK_H

#include <atomic>

namespace chip8 {

/**
 * Simple and light-weight spin-lock critical section.
 * It is useful to gain access to small (short-timed) code.
 */
class Spinlock {
 public:
  /**
   * Constructs free (unlocked) spin.
   */
  Spinlock();

  Spinlock(const Spinlock&) = delete;
  Spinlock(Spinlock&&) = delete;
  Spinlock& operator=(const Spinlock&) = delete;
  Spinlock& operator=(Spinlock&&) = delete;

  /**
   * Returns true if the spin is locked, or false otherwise.
   */
  bool isLocked() const;

  /**
   * Tries to lock the object.
   * Returns true if locking is succeeded
   * otherwise (if the spin is already locked) returns false.
   */
  bool tryLock();

  /**
   * Locks the spin. Waits infinitely while spin is locked.
   */
  void lock();

  /**
   * Unlocks the spin.
   */
  void unlock();

 private:
  std::atomic_bool spin_;
};

} // namespace chip8

#endif // CHIP8_BASE_SPINLOCK_H
