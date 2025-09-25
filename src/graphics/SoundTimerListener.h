#ifndef CHIP8_GRAPHICS_SOUNDTIMERLISTENER_H
#define CHIP8_GRAPHICS_SOUNDTIMERLISTENER_H

namespace chip8 {

class SoundTimerListener {
 public:
  virtual ~SoundTimerListener() {}

  virtual void onTimerStart() = 0;

  virtual void onTimerStop() = 0;

  virtual void onTimerInterrupt() = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_SOUNDTIMERLISTENER_H
