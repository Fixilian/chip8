#include "ExecutionContext.h"

namespace chip8 {

constexpr int kCommonRegistersNumber = 16;


ExecutionContext::ExecutionContext(int stack_size, Ram& ram, 
                                    int frame_w, int frame_h)
    : registers(kCommonRegistersNumber),
      pc(nullptr),
      i(0),
      ram(ram),
      frame(frame_w, frame_h),
      stack(stack_size),
      dt_(0),
      st_(0)
{}
 

byte ExecutionContext::dt() {
  return dt_;
}


byte ExecutionContext::st() {
  return st_;
}


void ExecutionContext::updateTimers() {
  if (st_ > 0) {
    st_ -= 1;
  }
  if (dt_ > 0) {
    dt_ -= 1;
  }
}


} // namespace chip8
