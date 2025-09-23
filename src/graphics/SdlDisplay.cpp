#include "SdlDisplay.h"

#include "base/Log.h"

namespace chip8 {

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };


SdlDisplay::SdlDisplay(int w, int h)
    : window_(nullptr),
      renderer_(nullptr),
      width_(w),
      height_(h)
{}


SdlDisplay::~SdlDisplay() {
  // Destroy renderer and window

  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  SDL_DestroyWindow(window_);
  window_ = nullptr;
}


bool SdlDisplay::init() {
  bool success = SDL_CreateWindowAndRenderer(
    "Chip8 emulator", kScreenWidth, kScreenHeight, 
    0, &window_, &renderer_); 
  if (!success) {
    Log::error("Window/renderer could not be created! SDL error: {}", SDL_GetError());
  }
  return success;
}


void SdlDisplay::render(const Frame& frame) {
  // RGB (51 3 47) dark purple
  SDL_SetRenderDrawColor(renderer_, 51, 3, 47, SDL_ALPHA_OPAQUE);
  // start with a blank canvas
  SDL_RenderClear(renderer_);

  int cell_w = kScreenWidth / width_;
  int cell_h = kScreenHeight / height_;
  SDL_FRect rect;
  rect.w = static_cast<float>(cell_w);
  rect.h = static_cast<float>(cell_h);
  // RGB (160 172 173) cadet gray 
  SDL_SetRenderDrawColor(renderer_, 160, 172, 173, SDL_ALPHA_OPAQUE);
  // draw pixels
  for (int y = 0; y < height_; y += 1) {
    for (int x = 0; x < width_; x += 1) {
      auto pixel = frame.getPixel(x, y);
      if (pixel) {
        rect.x = static_cast<float>(x * cell_w);
        rect.y = static_cast<float>(y * cell_h);
        SDL_RenderFillRect(renderer_, &rect);
      }
    }
  }

  // put it all on the screen
  SDL_RenderPresent(renderer_); 
}


} // namespace chip8
