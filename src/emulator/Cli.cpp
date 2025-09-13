#include "Cli.h"

#include <CLI/CLI.hpp>

#include "base/Log.h"
#include "Version.h"

using namespace std;

namespace chip8 {


CommandLineArguments parse(int argc, char** argv) {
  CLI::App cli{"Chip8 emulator"};
  argv = cli.ensure_utf8(argv);
  CommandLineArguments args;

  cli.set_version_flag("--version", string(CHIP8_VERSION));

  auto* rom_opt = cli.add_option("rom", args.rom_file, "ROM file name");
  rom_opt->required();

  auto* binary_flag = 
    cli.add_flag("-b", args.is_binary_rom, "Interpret rom file as binary");

  bool is_text_rom = false;
  auto* txt_flag = 
    cli.add_flag("-t", is_text_rom, "Interpret rom file as hexadecimal text");
  txt_flag->excludes(binary_flag);

  cli.add_option("-c,--cfg", args.cfg_file, "Config file name");

  cli.add_option("--mem_size", args.memory_size, "RAM size");

  cli.add_option("--stack_size", args.stack_size, "Stack size");

  cli.add_option("--display_width", args.display_width, "Display width");

  cli.add_option("--display_height", args.display_height, "Display height");

  try {
    Log::debug("Starting argv parsing");
    cli.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    args.err = cli.exit(e);
    args.exit = true;
  }

  if (is_text_rom) {
    args.is_binary_rom = false;
  }

  Log::info("Argv successfully parsed");
  return args;
}


} // namespace chip8
