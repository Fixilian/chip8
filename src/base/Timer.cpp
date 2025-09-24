#include "Timer.h"

using namespace std;

namespace chip8 {


Timer::Timer() 
    : running_(false)
{}


Timer::~Timer() {
  if (running_) {
    stop();
  }
}


void Timer::start(chrono::milliseconds interval, function<void()> callback) {
  running_ = true;
  thread_ = thread([this, interval, callback]() {
    while (running_) {
      this_thread::sleep_for(interval);
      if (running_) { // Check again in case stop() was called during sleep
        callback();
      }
    }
  });
}


void Timer::stop() {
  running_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
}


} // namespace chip8
