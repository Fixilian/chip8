#ifndef CHIP8_GRAPHICS_EVENTLOOP_H
#define CHIP8_GRAPHICS_EVENTLOOP_H

#include "EventListener.h"
#include "FrameListener.h"
#include "keyboard/KeyListener.h"

namespace chip8 {

class EventLoop : public FrameListener {
 public:
  virtual ~EventLoop() {}

  virtual bool init() = 0;

  virtual void start() = 0;

  virtual void stop() = 0;

  virtual void addEventListener(EventListener& listener) = 0;

  virtual void addKeyListener(KeyListener& listener) = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_EVENTLOOP_H
