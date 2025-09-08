#ifndef CHIP8_EMULATOR_COMMANDLINEARGUMENTS_H
#define CHIP8_EMULATOR_COMMANDLINEARGUMENTS_H

#include <string>

#include "configuration/MachineSpecification.h"

namespace chip8 {

class CommandLineArguments {
 public:
  CommandLineArguments(
    const std::string& rom_file, 
    bool is_binary_rom, 
    const std::string& cfg_file, 
    const MachineSpecification& spec);

  CommandLineArguments(const CommandLineArguments&) = default;
  CommandLineArguments& operator=(const CommandLineArguments&) = default;
  CommandLineArguments(CommandLineArguments&&) = default;
  CommandLineArguments& operator=(CommandLineArguments&&) = default;

  const std::string& getRomFile() const;

  bool isBinaryRom() const;

  const std::string& getCfgFile() const;

  const MachineSpecification& getSpecification() const;

 private:
  std::string rom_file_;
  bool is_binary_rom_;
  std::string cfg_file_;
  MachineSpecification spec_;
};

} // namespace chip8

#endif // CHIP8_EMULATOR_COMMANDLINEARGUMENTS_H
