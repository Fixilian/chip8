#include "ExecutionContext.h"

using namespace std;

namespace chip8 {

constexpr int kCommonRegistersNumber = 16;


ExecutionContext::ExecutionContext(
  int stack_size, 
  int frame_w, 
  int frame_h,
  Ram& ram,
  KeyboardMonitor& keyboard) 
    : registers(kCommonRegistersNumber),
      pc(nullptr),
      i(0),
      ram(ram),
      frame(frame_w, frame_h),
      stack(stack_size),
      keyboard(keyboard),
      dt_(0),
      st_(0)
{}
 

byte ExecutionContext::dt() {
  return dt_.load(memory_order_relaxed);
}


void ExecutionContext::setDt(byte val) {
  spin.lock();
  dt_.store(val, memory_order_relaxed);
  spin.unlock();
}


byte ExecutionContext::st() {
  return st_.load(memory_order_relaxed);
}


void ExecutionContext::setSt(byte val) {
  spin.lock();
  st_.store(val, memory_order_relaxed);
  spin.unlock();
}


void ExecutionContext::updateTimers() {
  spin.lock();
  if (st_ > 0) {
    st_ -= 1;
  }
  if (dt_ > 0) {
    dt_ -= 1;
  }
  spin.unlock();
}


} // namespace chip8
