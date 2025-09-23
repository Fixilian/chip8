#include "HexKeyboardMonitor.h"

#include "exception/UnknownKeyException.h"

using namespace std;

namespace chip8 {


HexKeyboardMonitor::HexKeyboardMonitor() 
    : pressed_(kNumberOfKeys),
      key_state_(KeyState::Received),
      last_pressed_key_(kNumberOfKeys)
{}


void HexKeyboardMonitor::onKeyPressed(byte key) {
  checkKey(key);
  pressed_[key] = true;
  if (key_state_ == KeyState::Requested) {
    last_pressed_key_ = key;
    key_state_ = KeyState::Pressed;
  }
}


void HexKeyboardMonitor::onKeyReleased(byte key) {
  checkKey(key);
  pressed_[key] = false;
  if (key_state_ == KeyState::Pressed && key == last_pressed_key_) {
    key_state_ = KeyState::Released;
    cv_.notify_all();
  }
}


bool HexKeyboardMonitor::pressed(byte key) const {
  if (key > kNumberOfKeys) {
    return false;
  }
  return pressed_[key];
}


bool HexKeyboardMonitor::operator[](byte key) const {
  return pressed(key);
}


byte HexKeyboardMonitor::waitKeyPress() {
  byte key = 0;
  {
    unique_lock<mutex> lock(mtx_);
    key_state_ = KeyState::Requested;
    cv_.wait(lock, [&] { return key_state_ == KeyState::Released; });
    key = last_pressed_key_;
    key_state_ = KeyState::Received;
  }
  return key;
}


void HexKeyboardMonitor::checkKey(byte key) {
  if (key >= kNumberOfKeys) {
    throw UnknownKeyException(key, "Unsupported key value");
  }
}


} // namespace chip8;
