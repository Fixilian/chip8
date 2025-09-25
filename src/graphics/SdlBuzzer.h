#ifndef CHIP8_GRAPHICS_ONETONEBUZZER_H
#define CHIP8_GRAPHICS_ONETONEBUZZER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

#include "Buzzer.h"

namespace chip8 {

class SdlBuzzer : public Buzzer {
 public:
  SdlBuzzer();

  virtual ~SdlBuzzer() {}

  virtual bool init() override;

  virtual void buzz() override;
 
 private:
  SDL_AudioStream* audio_stream_;
  std::vector<float> audio_samples_;
  int current_sine_sample_;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_ONETONEBUZZER_H
