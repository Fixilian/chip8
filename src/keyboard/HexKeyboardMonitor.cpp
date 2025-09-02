#include "HexKeyboardMonitor.h"

#include "exception/UnknownKeyException.h"

using namespace std;

namespace chip8 {


HexKeyboardMonitor::HexKeyboardMonitor() 
    : pressed_(kNumberOfKeys)
{}


void HexKeyboardMonitor::onKeyPressed(byte key) {
  checkKey(key);
  pressed_[key] = true;
  {
    lock_guard<mutex> lock(mtx_);
    last_pressed_key_ = key;
    key_pressed_ = true;
  }
  cv_.notify_all();
}


void HexKeyboardMonitor::onKeyReleased(byte key) {
  checkKey(key);
  pressed_[key] = false;
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
    cv_.wait(lock, [&] { return key_pressed_; });
    key = last_pressed_key_;
    key_pressed_ = false;
  }
  return key;
}


void HexKeyboardMonitor::checkKey(byte key) {
  if (key >= kNumberOfKeys) {
    throw UnknownKeyException(key, "Unsupported key value");
  }
}


} // namespace chip8;
