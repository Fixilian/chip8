set(SOURCES
  base/Allocator.cpp
  base/BitOperations.cpp
  base/FileIO.cpp
  base/Log.cpp
  base/Rom.cpp
  base/Spinlock.cpp
  base/Timer.cpp

  compiler/Compiler.cpp
  compiler/HexRomParser.cpp
  compiler/RomBuilder.cpp

  configuration/Config.cpp
  configuration/JsonConfig.cpp
  configuration/KeybindTable.cpp
  configuration/MachineSpecification.cpp

  emulator/Cli.cpp
  emulator/Emulator.cpp

  exception/Exception.cpp
  exception/InvalidArgumentException.cpp
  exception/InvalidConfigException.cpp
  exception/IOException.cpp
  exception/OutOfRangeException.cpp
  exception/SegFaultException.cpp
  exception/SemanticException.cpp
  exception/SyntaxException.cpp
  exception/UnknownKeyException.cpp

  execution/Chip8Decoder.cpp
  execution/Cpu.cpp
  execution/EndOfProgramDetector.cpp

  graphics/Frame.cpp
  graphics/SdlDisplay.cpp

  instruction/AddIInstruction.cpp
  instruction/AddRegisterInstruction.cpp
  instruction/AddValueInstruction.cpp
  instruction/BitwiseAndInstruction.cpp
  instruction/BitwiseOrInstruction.cpp
  instruction/BitwiseXorInstruction.cpp
  instruction/CallInstruction.cpp
  instruction/ClearDisplayInstruction.cpp
  instruction/DrawInstruction.cpp
  instruction/ExecutionContext.cpp
  instruction/GetSpriteLocationInstruction.cpp
  instruction/Instruction.cpp
  instruction/InstructionPtr.cpp
  instruction/JumpInstruction.cpp
  instruction/JumpWithOffsetInstruction.cpp
  instruction/LoadDtInstruction.cpp
  instruction/LoadInstruction.cpp
  instruction/LoadIRegisterInstruction.cpp
  instruction/LoadRegisterInstruction.cpp
  instruction/LoadValueInstruction.cpp
  instruction/RandomInstruction.cpp
  instruction/ReturnInstruction.cpp
  instruction/SetDelayTimerInstruction.cpp
  instruction/SetSoundTimerInstruction.cpp
  instruction/ShiftLeftInstruction.cpp
  instruction/ShiftRightInstruction.cpp
  instruction/SkipIfEqRegisterInstruction.cpp
  instruction/SkipIfEqValueInstruction.cpp
  instruction/SkipIfNeRegisterInstruction.cpp
  instruction/SkipIfNeValueInstruction.cpp
  instruction/SkipIfNotPressedInstruction.cpp
  instruction/SkipIfPressedInstruction.cpp
  instruction/StoreBcdInstruction.cpp
  instruction/StoreInstruction.cpp
  instruction/SubnInstruction.cpp
  instruction/SubRegisterInstruction.cpp
  instruction/SysJumpInstruction.cpp
  instruction/WaitKeyPressInstruction.cpp

  keyboard/HexKeyboardMonitor.cpp
  keyboard/SdlKeyAdapter.cpp

  memory/FixedMemory.cpp
)

add_library(libchip8 ${SOURCES})

target_link_libraries(libchip8 PRIVATE
  nlohmann_json::nlohmann_json
  CLI11::CLI11
  SDL3::SDL3
  spdlog::spdlog
)

target_compile_options(libchip8 PRIVATE
  -Werror

  -Wall
  -Wextra
  -Wpedantic

  -Wcast-align
  -Wcast-qual
  -Wconversion
  -Wctor-dtor-privacy
  -Wenum-compare
  -Wfloat-equal
  -Wnon-virtual-dtor

  # SDL is written in С
  # -Wold-style-cast
  
  -Woverloaded-virtual
  -Wredundant-decls
  -Wsign-promo
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  libchip8
)
