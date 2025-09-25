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
      st_(0),
      st_state_(StState::Stopped)
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
  updateStState();
}


void ExecutionContext::addFrameListener(FrameListener& listener) {
  frame_listeners_.push_back(&listener);
}


void ExecutionContext::notifyFrameListeners() {
  for (size_t i = 0; i < frame_listeners_.size(); i += 1) {
    frame_listeners_[i]->onChange(frame);
  }
}


bool ExecutionContext::areListenersReady() {
  for (size_t i = 0; i < frame_listeners_.size(); i += 1) {
    if (!frame_listeners_[i]->isReady()) {
      return false;
    }
  }
  return true;
}


void ExecutionContext::addSoundTimerListener(SoundTimerListener& listener) {
  st_listeners_.push_back(&listener);
}


void ExecutionContext::updateStState() {
  switch (st_state_) {
    case StState::Started:
      if (st_ == 0) {
        st_state_ = StState::Stopped;
        notifySoundTimerListeners(st_state_);
      } else {
        notifySoundTimerListeners(StState::Interrupted);
      }
      break;

    case StState::Stopped:
      if (st_ > 0) {
        st_state_ = StState::Started;
        notifySoundTimerListeners(st_state_);
      }
      break;
    
    default: break;
  }
}


void ExecutionContext::notifySoundTimerListeners(StState state) {
  for (size_t i = 0; i < st_listeners_.size(); i += 1) {
    auto& l = st_listeners_[i];
    switch (state) {
      case StState::Started: l->onTimerStart(); break;
      case StState::Stopped: l->onTimerStop(); break;
      case StState::Interrupted: l->onTimerInterrupt(); break;
      default: break;
    }
  }
}


string ExecutionContext::toString() const {
  stringstream stream;
  word cur_pc = static_cast<word>(pc - ram.mem());
  stream << "PC=" << cur_pc << " I=" << i << '\n';
  stream << setfill(' ');
  int n = static_cast<int>(registers.size());
  for (int i = 0; i < n; i += 1) {
    stream << setw(6) << i;
  }
  stream << '\n';
  for (int i = 0; i < n; i += 1) {
    unsigned int val = registers[i];
    stream << setw(6) << to_string(val);
  }
  if (!stack.empty()) {
    stream << '\n';
    stream << "Stack: {\n";
    for (auto val : stack) {
      stream << val << '\n';
    } 
    stream << '}';
  }
  return stream.str();
}


} // namespace chip8
