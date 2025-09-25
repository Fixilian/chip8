#ifndef CHIP8_GRAPHICS_EVENTLISTENER_H
#define CHIP8_GRAPHICS_EVENTLISTENER_H

namespace chip8 {

class EventListener {
 public:
  virtual ~EventListener() {}

  virtual void onClose() = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_EVENTLISTENER_H
