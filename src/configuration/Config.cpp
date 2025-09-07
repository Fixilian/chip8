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
  keybinds_.bindKey('1', 0x1);
  keybinds_.bindKey('2', 0x2);
  keybinds_.bindKey('3', 0x3);
  keybinds_.bindKey('4', 0xC);
  keybinds_.bindKey('q', 0x4);
  keybinds_.bindKey('w', 0x5);
  keybinds_.bindKey('e', 0x6);
  keybinds_.bindKey('r', 0xD);
  keybinds_.bindKey('a', 0x7);
  keybinds_.bindKey('s', 0x8);
  keybinds_.bindKey('d', 0x9);
  keybinds_.bindKey('f', 0xE);
  keybinds_.bindKey('z', 0xA);
  keybinds_.bindKey('x', 0x0);
  keybinds_.bindKey('c', 0xB);
  keybinds_.bindKey('v', 0xF);
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
