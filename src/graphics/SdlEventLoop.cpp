#include "SdlEventLoop.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "base/Log.h"
#include "base/Spinlock.h"
#include "SdlDisplay.h"

using namespace std;

namespace chip8 {


SdlEventLoop::SdlEventLoop(int w, int h, const KeybindTable& binds) 
    : display_(make_unique<SdlDisplay>(w, h)),
      frame_(w, h),
      running_(false),
      binds_(binds),
      redraw_event_type_(0)
{}


SdlEventLoop::~SdlEventLoop() {
  //Quit SDL subsystems
  SDL_Quit();
}


bool SdlEventLoop::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    Log::error("SDL could not initialize! SDL error: {}", SDL_GetError());
    return false;
  } else {
    redraw_event_type_ = SDL_RegisterEvents(1);
    if (redraw_event_type_ == static_cast<Uint32>(-1)) {
      Log::error("SDL could not register events");
      return false;
    } else {
      return display_->init();
    }
  }
}


void SdlEventLoop::start() {
  SDL_Event e;
  SDL_zero(e);
  display_->render(frame_);
  running_ = true;
  while (running_) {
    // Get event data
    while (SDL_PollEvent(&e) == true) {
      switch (e.type) {
        case SDL_EVENT_QUIT: onQuit(); break;
        case SDL_EVENT_KEY_DOWN: onKeyDown(e); break;
        case SDL_EVENT_KEY_UP: onKeyUp(e); break; 
        default: onCustomEvent(e); break;
      }
    }
  }
}


void SdlEventLoop::stop() {
  running_ = false;
}


void SdlEventLoop::onChange(const Frame& frame) {
  spin_.lock();
  frame_.copy(frame);
  spin_.unlock();
  SDL_Event e;
  SDL_zero(e);
  e.type = redraw_event_type_;
  bool success = SDL_PushEvent(&e);
  if (!success) {
    Log::error("Redraw event push failed: {}", SDL_GetError());
  }
}


void SdlEventLoop::addEventListener(EventListener& listener) {
  event_listeners_.push_back(&listener);
}


void SdlEventLoop::addKeyListener(KeyListener& listener) {
  key_listeners_.push_back(&listener);
}


void SdlEventLoop::onQuit() {
  stop();
  for (size_t i = 0; i < event_listeners_.size(); i += 1) {
    event_listeners_[i]->onClose();
  }
}


void SdlEventLoop::onKeyDown(const SDL_Event& e) {
  auto key_code = e.key.scancode;
  if (key_code == binds_.getQuitKey()) {
    onQuit();
    return;
  }
  if (binds_.contains(key_code)) {
    for (size_t i = 0; i < key_listeners_.size(); i += 1) {
      key_listeners_[i]->onKeyPressed(binds_[key_code]);
    }
  }
}


void SdlEventLoop::onKeyUp(const SDL_Event& e) {
  auto key_code = e.key.scancode;
  if (binds_.contains(key_code)) {
    for (size_t i = 0; i < key_listeners_.size(); i += 1) {
      key_listeners_[i]->onKeyReleased(binds_[key_code]);
    }
  }
}


void SdlEventLoop::onCustomEvent(const SDL_Event& e) {
  if (e.type == redraw_event_type_) {
    onRedraw();
  }
}


void SdlEventLoop::onRedraw() {
  Log::debug("Event loop redraw event");
  spin_.lock();
  display_->render(frame_);
  spin_.unlock();
}


} // namespace chip8
