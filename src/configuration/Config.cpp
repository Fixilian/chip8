#include "Config.h"

using namespace std;

namespace chip8 {


Config::Config(const MachineSpecification& spec, const KeybindTable& keybinds) 
    : spec_(spec),
      keybinds_(keybinds)
{}


Config::Config(const MachineSpecification& spec) 
    : spec_(spec)
{
  // 16-key keypad
  // 1 2 3 C
  // 4 5 6 D
  // 7 8 9 E
  // A 0 B F

  // default keybinds for WASD keyboard
  keybinds_.bindKey("1", 0x1);
  keybinds_.bindKey("2", 0x2);
  keybinds_.bindKey("3", 0x3);
  keybinds_.bindKey("4", 0xC);
  keybinds_.bindKey("Q", 0x4);
  keybinds_.bindKey("W", 0x5);
  keybinds_.bindKey("E", 0x6);
  keybinds_.bindKey("R", 0xD);
  keybinds_.bindKey("A", 0x7);
  keybinds_.bindKey("S", 0x8);
  keybinds_.bindKey("D", 0x9);
  keybinds_.bindKey("F", 0xE);
  keybinds_.bindKey("Z", 0xA);
  keybinds_.bindKey("X", 0x0);
  keybinds_.bindKey("C", 0xB);
  keybinds_.bindKey("V", 0xF);
}


MachineSpecification& Config::getSpecification() {
  return spec_;
}


const MachineSpecification& Config::getSpecification() const {
  return spec_;
}


KeybindTable& Config::getKeyBinds() {
  return keybinds_;
}


const KeybindTable& Config::getKeyBinds() const {
  return keybinds_;
}


} // namespace chip8
