#include "CommandLineArguments.h"

using namespace std;

namespace chip8 {


CommandLineArguments::CommandLineArguments(
  const string& rom_file, 
  bool is_binary_rom, 
  const string& cfg_file, 
  const MachineSpecification& spec)
    : rom_file_(rom_file),
      is_binary_rom_(is_binary_rom),
      cfg_file_(cfg_file),
      spec_(spec)
{}


const string& CommandLineArguments::getRomFile() const {
  return rom_file_;
}


bool CommandLineArguments::isBinaryRom() const {
  return is_binary_rom_;
}


const string& CommandLineArguments::getCfgFile() const {
  return cfg_file_;
}


const MachineSpecification& CommandLineArguments::getSpecification() const {
  return spec_;
}


} // namespace chip8
