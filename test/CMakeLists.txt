set(SOURCES
  base/AllocatorTest.cpp
  base/BitOperationsTest.cpp
  base/StackTest.cpp
  
  compiler/CompilerTest.cpp
  compiler/HexRomParserTest.cpp
  compiler/RomBuilderTest.cpp

  configuration/JsonConfigTest.cpp
  configuration/KeybindTableTest.cpp
  configuration/MachineSpecificationTest.cpp

  execution/Chip8DecoderTest.cpp
  execution/CpuTest.cpp
  execution/EndOfProgramDetectorTest.cpp

  graphics/FrameTest.cpp

  instruction/AddIInstructionTest.cpp
  instruction/AddRegisterInstructionTest.cpp
  instruction/AddValueInstructionTest.cpp
  instruction/BitwiseAndInstructionTest.cpp
  instruction/BitwiseOrInstructionTest.cpp
  instruction/BitwiseXorInstructionTest.cpp
  instruction/CallInstructionTest.cpp
  instruction/ClearDisplayInstructionTest.cpp
  instruction/DrawInstructionTest.cpp
  instruction/GetSpriteLocationInstructionTest.cpp
  instruction/InstructionPtrTest.cpp
  instruction/JumpInstructionTest.cpp
  instruction/JumpWithOffsetInstructionTest.cpp
  instruction/LoadDtInstructionTest.cpp
  instruction/LoadInstructionTest.cpp
  instruction/LoadIRegisterInstructionTest.cpp
  instruction/LoadRegisterInstructionTest.cpp
  instruction/LoadValueInstructionTest.cpp
  instruction/RandomInstructionTest.cpp
  instruction/ReturnInstructionTest.cpp
  instruction/SetDelayTimerInstructionTest.cpp
  instruction/SetSoundTimerInstructionTest.cpp
  instruction/ShiftLeftInstructionTest.cpp
  instruction/ShiftRightInstructionTest.cpp
  instruction/SkipIfEqRegisterInstructionTest.cpp
  instruction/SkipIfEqValueInstructionTest.cpp
  instruction/SkipIfNeRegisterInstructionTest.cpp
  instruction/SkipIfNeValueInstructionTest.cpp
  instruction/SkipIfNotPressedInstructionTest.cpp
  instruction/SkipIfPressedInstructionTest.cpp
  instruction/StoreBcdInstructionTest.cpp
  instruction/StoreInstructionTest.cpp
  instruction/SubnInstructionTest.cpp
  instruction/SubRegisterInstructionTest.cpp

  keyboard/HexKeyboardMonitorTest.cpp

  memory/FixedMemoryTest.cpp

  TestObjectFactory.cpp
)

add_executable(chiptests ${SOURCES})

target_link_libraries(chiptests PRIVATE
  GTest::gtest_main
  nlohmann_json::nlohmann_json
  libchip8
)

include_directories("./")

include(GoogleTest)
gtest_discover_tests(chiptests)

target_compile_options(chiptests PRIVATE
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
  -Wold-style-cast
  -Woverloaded-virtual
  -Wredundant-decls
  -Wsign-promo
)
