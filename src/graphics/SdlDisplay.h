#ifndef CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H
#define CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Display.h"

namespace chip8 {

class SdlDisplay : public Display {
 public:
  SdlDisplay(int w, int h); 

  virtual ~SdlDisplay();

  virtual bool init() override;

  virtual void render(const Frame& frame) override;

 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  int width_;
  int height_;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_MONOCHROMEDISPLAY_H
