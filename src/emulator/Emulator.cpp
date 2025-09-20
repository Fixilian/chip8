#include "Emulator.h"

#include <iostream>
#include <memory>
#include <thread>

#include "base/Endian.h"
#include "base/FileIO.h"
#include "base/Log.h"
#include "base/Rom.h"
#include "Cli.h"
#include "compiler/Compiler.h"
#include "configuration/Config.h"
#include "configuration/JsonConfig.h"
#include "configuration/MachineSpecification.h"
#include "exception/Exception.h"
#include "exception/IOException.h"
#include "execution/Cpu.h"
#include "graphics/SdlEventLoop.h"
#include "instruction/ExecutionContext.h"
#include "keyboard/HexKeyboardMonitor.h"
#include "memory/FixedMemory.h"

using namespace std;

namespace chip8 {


class EventLoopListener : public EventListener {
 public:
  EventLoopListener(Cpu& cpu) 
      : cpu_(cpu)
  {}

  virtual ~EventLoopListener() {}

  virtual void onClose() override {
    cpu_.stop();
  }

 private:
  Cpu& cpu_;
};


static Config getConfig(const CommandLineArguments& args) {
  MachineSpecification default_spec;
  Config cfg(default_spec);

  try {
    Log::debug("Starting config reading");
    int max_cfg_len = 1024;
    string json_cfg = readFile(args.cfg_file, max_cfg_len);
    Config c = readFromJson(json_cfg);
    cfg = std::move(c);
  } catch (const IOException& ex) {
    Log::warn(ex.message());
    Log::info("Cannot read cfg from file");
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

  Log::info("Config successfully generated");
  return cfg;
}  


static void startEventLoopAndCpu(EventLoop& event_loop, Cpu& cpu, Rom rom) {
  thread event_thread([&]() {
    try {
      Log::debug("Initializing event loop");
      bool success = event_loop.init();
      if (!success) {
        Log::error("Event loop initialization failed");
        return;
      }
      Log::info("Event loop successfully initialized");

      Log::info("Starting cpu thread");
      thread cpu_thread([&]() {
        try {
          Log::info("Starting execution");
          cpu.execute(rom);
          Log::info("End of programm");
        } catch(const Exception& ex) {
          Log::error(ex.message());
        }
        // event_loop.stop();
        Log::info("Cpu thread stopped");
      });

      Log::info("Starting event loop");
      event_loop.start();
      if (cpu_thread.joinable()) {
        cpu_thread.join();
      }
    } catch(const exception& ex) {
      Log::error(ex.what());
    }
    Log::info("Event loop thread stopped");
  }); 
  if (event_thread.joinable()) {
    event_thread.join();
  }
}


static void execute(Rom rom, const Config& cfg, Endianness endian) {
  auto& spec = cfg.getSpecification();
  auto& keybinds = cfg.getKeyBinds();

  Log::debug("Initializing hardware components");
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

  Cpu cpu(*memory, ctx, endian);

  auto event_loop = make_unique<SdlEventLoop>(
    spec.getDisplayWidth(),
    spec.getDisplayHeight(),
    keybinds);

  EventLoopListener event_loop_listener(cpu);

  event_loop->addKeyListener(*keyboard);
  event_loop->addEventListener(event_loop_listener);

  ctx.addFrameListener(*event_loop);
  Log::info("Hardware components successfully initialized");

  startEventLoopAndCpu(*event_loop, cpu, rom);
}


int Emulator::run(int argc, char** argv) {
  bool enable_console = true;
  bool success = Log::init(enable_console);
  if (!success) {
    return 1;
  }
  Log::setLevel(LogLevel::Debug);

  auto args = parse(argc, argv);
  if (args.exit) {
    Log::info("Exit after argv parsing");
    return args.err;
  }

  try {
    Config cfg = getConfig(args);
    MachineSpecification& spec = cfg.getSpecification();

    if (args.is_binary_rom) {

      Log::info("Starting binary ROM execution");
      Rom rom = fromFile(args.rom_file, spec.getMemorySize());
      execute(rom, cfg, Endianness::BigEndian);

    } else {

      Log::info("Starting ROM compilation");
      Compiler compiler(spec, true);
      Rom rom = compiler.compile(args.rom_file);

      Log::info("Starting ROM execution");
      execute(rom, cfg, Endianness::LittleEndian);

    }

  } catch(const Exception& ex) {
    Log::error(ex.message());
  }

  return 0;
}


} // namespace chip8
