#ifndef CHIP8_CONFIGURATION_CONFIG_H
#define CHIP8_CONFIGURATION_CONFIG_H

#include "KeybindTable.h"
#include "MachineSpecification.h"

namespace chip8 {

class Config {
 public:
  Config(const MachineSpecification& spec, const KeybindTable& keybinds);
  Config(const MachineSpecification& spec);

  Config(const Config&) = default;
  Config& operator=(const Config&) = default;
  Config(Config&&) = default;
  Config& operator=(Config&&) = default;

  MachineSpecification& getSpecification();
  const MachineSpecification& getSpecification() const;

  KeybindTable& getKeyBinds();
  const KeybindTable& getKeyBinds() const;

 private:
  MachineSpecification spec_;
  KeybindTable keybinds_;
};

} // namespace chip8

#endif // CHIP8_CONFIGURATION_CONFIG_H
