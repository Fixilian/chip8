#include "Cli.h"

#include <CLI/CLI.hpp>
#include <string>

#include "configuration/MachineSpecification.h"

using namespace std;

namespace chip8 {


CommandLineArguments parse(int argc, char** argv, int& err) {
  err = 0;
  CLI::App cli{"Chip8 emulator"};
  argv = cli.ensure_utf8(argv);

  cli.set_version_flag("--version", string("")); // TODO

  string rom = "";
  auto* rom_opt = cli.add_option("rom", rom, "ROM file name");
  rom_opt->required();

  bool is_binary_rom = true;
  auto* binary_flag = 
    cli.add_flag("-b", is_binary_rom, "Interpret rom file as binary");

  bool is_text_rom = false;
  auto* txt_flag = 
    cli.add_flag("-t", is_text_rom, "Interpret rom file as hexadecimal text");
  txt_flag->excludes(binary_flag);

  string cfg = "default.cfg";
  cli.add_option("-c,--cfg", cfg, "Config file name");

  MachineSpecification spec;

  int memory_size = spec.getMemorySize();
  cli.add_option("--mem_size", memory_size, "RAM size");

  int stack_size = spec.getStackSize();
  cli.add_option("--stack_size", stack_size, "Stack size");

  int display_width = spec.getDisplayWidth();
  cli.add_option("--display_width", display_width, "Display width");

  int display_height = spec.getDisplayHeight();
  cli.add_option("--display_height", display_height, "Display height");

  try {
    cli.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    err = cli.exit(e);
  }

  if (is_text_rom) {
    is_binary_rom = false;
  }
  spec.setMemorySize(memory_size);
  spec.setStackSize(stack_size);
  spec.setDisplayWidth(display_width);
  spec.setDisplayHeight(display_height);

  CommandLineArguments args(rom, is_binary_rom, cfg, spec);
  return args;
}


} // namespace chip8
