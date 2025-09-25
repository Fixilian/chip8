#ifndef CHIP8_EMULATOR_CLI_H
#define CHIP8_EMULATOR_CLI_H

#include <string>

namespace chip8 {

struct CommandLineArguments {
  int err = 0;
  bool exit = false;
  std::string rom_file = "";
  bool is_binary_rom = true;
  std::string cfg_file = "default.cfg";
  int memory_size = 0;
  int stack_size = 0;
  int display_width = 0;
  int display_height = 0;
};

/**
 * Parses command line arguments.
 * @param[out] err - > 0 if some error occur, otherwise = 0.
 */
CommandLineArguments parse(int argc, char** argv);

} // namespace chip8

#endif // CHIP8_EMULATOR_CLI_H
