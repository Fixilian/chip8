#ifndef CHIP8_GRAPHICS_SDLEVENTLOOP_H
#define CHIP8_GRAPHICS_SDLEVENTLOOP_H

#include <atomic>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

#include "base/Spinlock.h"
#include "configuration/KeybindTable.h"
#include "Display.h"
#include "EventLoop.h"
#include "Frame.h"

namespace chip8 {

class SdlEventLoop : public EventLoop {
 public:
  SdlEventLoop(int w, int h, const KeybindTable& binds);

  virtual ~SdlEventLoop();

  virtual bool init() override;

  virtual void start() override;

  virtual void stop() override;

  virtual void onChange(const Frame& frame) override;

  virtual void addEventListener(EventListener& listener) override;

  virtual void addKeyListener(KeyListener& listener) override;

 private:
  std::vector<EventListener*> event_listeners_;
  std::vector<KeyListener*> key_listeners_;
  std::unique_ptr<Display> display_;
  Spinlock spin_;
  Frame frame_;
  std::atomic<bool> running_;
  const KeybindTable& binds_;
  Uint32 redraw_event_type_;

  void onQuit();
  void onKeyDown(const SDL_Event& e);
  void onKeyUp(const SDL_Event& e);
  void onCustomEvent(const SDL_Event& e);
  void onRedraw();
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_SDLEVENTLOOP_H
