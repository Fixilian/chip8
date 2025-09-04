#ifndef CHIP8_BASE_TIMER_H
#define CHIP8_BASE_TIMER_H

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

namespace chip8 {

/**
 * Timer thread.
 * Executes callback at regular intervals. 
 * Does not execute callback when the timer starts.
 */
class Timer {
 public:
  Timer();

  ~Timer();

  void start(std::chrono::milliseconds interval, std::function<void()> callback);

  void stop();

 private:
  std::thread thread_;
  std::atomic<bool> running_;
};

} // namespace chip8

#endif // CHIP8_BASE_TIMER_H
