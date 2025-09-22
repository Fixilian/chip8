#include "ExecutionContext.h"

#include <iomanip>
#include <sstream>

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


void ExecutionContext::addFrameListener(FrameListener& listener) {
  frame_listeners_.push_back(&listener);
}


void ExecutionContext::notifyFrameListeners() {
  for (size_t i = 0; i < frame_listeners_.size(); i += 1) {
    frame_listeners_[i]->onChange(frame);
  }
}


string ExecutionContext::toString() const {
  stringstream stream;
  word cur_pc = static_cast<word>(pc - ram.mem());
  stream << "PC=" << cur_pc << " I=" << i << '\n';
  stream << setw(6);
  int n = static_cast<int>(registers.size());
  for (int i = 0; i < n; i += 1) {
    stream << i;
  }
  stream << '\n';
  for (int i = 0; i < n; i += 1) {
    stream << registers[i];
  }
  stream << '\n';
  stream << setw(1);
  stream << "Stack: {\n";
  for (auto val : stack) {
    stream << val << '\n';
  } 
  stream << '}';
  return stream.str();
}


} // namespace chip8
