#include "Emulator.h"

#include <iostream>
#include <memory>

#include "base/FileIO.h"
#include "base/Rom.h"
#include "Cli.h"
#include "compiler/Compiler.h"
#include "configuration/Config.h"
#include "configuration/JsonConfig.h"
#include "configuration/MachineSpecification.h"
#include "exception/Exception.h"
#include "exception/IOException.h"
#include "execution/Cpu.h"
#include "instruction/ExecutionContext.h"
#include "keyboard/HexKeyboardMonitor.h"
#include "memory/FixedMemory.h"

using namespace std;

namespace chip8 {


static Config getConfig(const CommandLineArguments& args) {
  MachineSpecification default_spec;
  Config cfg(default_spec);

  try {
    int max_cfg_len = 1024;
    string json_cfg = readFile(args.cfg_file, max_cfg_len);
    Config c = readFromJson(json_cfg);
    cfg = std::move(c);
  } catch (const IOException& _) {
    // cfg not found
  }

  auto spec = cfg.getSpecification();
  if (args.memory_size > 0) {
    spec.setMemorySize(args.memory_size);
  }
  if (args.stack_size > 0) {
    spec.setStackSize(args.stack_size);
  }
  if (args.display_width > 0) {
    spec.setDisplayWidth(args.display_width);
  }
  if (args.display_height > 0) {
    spec.setDisplayHeight(args.display_height);
  }

  return cfg;
}  


static void execute(Rom rom, const Config& cfg) {
  auto spec = cfg.getSpecification();
  auto keyboard = make_unique<HexKeyboardMonitor>();
  auto memory = make_unique<FixedMemory>(
    spec.getMemorySize(), 
    spec.getReservedMemorySize()
  );
  ExecutionContext ctx(
    spec.getStackSize(),
    spec.getDisplayWidth(),
    spec.getDisplayHeight(), 
    *memory,
    *keyboard
  ); 
  Cpu cpu(*memory, ctx);
  cpu.execute(rom);
}


int Emulator::run(int argc, char** argv) {
  auto args = parse(argc, argv);
  if (args.exit) {
    return args.err;
  }

  try {
    Config cfg = getConfig(args);
    MachineSpecification& spec = cfg.getSpecification();

    if (args.is_binary_rom) {
      Rom rom = fromFile(args.rom_file, spec.getMemorySize());
      execute(rom, cfg);
    } else {
      Compiler compiler(spec, true);
      Rom rom = compiler.compile(args.rom_file);
      execute(rom, cfg);
    }

  } catch(const Exception& ex) {
    cerr << ex;
  }

  return 0;
}


} // namespace chip8
