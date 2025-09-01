set(SOURCES
  base/BitOperationsTest.cpp
  base/StackTest.cpp
  
  compiler/CompilerTest.cpp
  compiler/HexRomParserTest.cpp
  compiler/RomBuilderTest.cpp

  graphics/FrameTest.cpp

  instruction/AddRegisterInstructionTest.cpp
  instruction/AddValueInstructionTest.cpp
  instruction/BitwiseAndInstructionTest.cpp
  instruction/BitwiseOrInstructionTest.cpp
  instruction/BitwiseXorInstructionTest.cpp
  instruction/CallInstructionTest.cpp
  instruction/ClearDisplayInstructionTest.cpp
  instruction/InstructionTestBase.cpp
  instruction/JumpInstructionTest.cpp
  instruction/LoadRegisterInstructionTest.cpp
  instruction/LoadValueInstructionTest.cpp
  instruction/ReturnInstructionTest.cpp
  instruction/ShiftRightInstructionTest.cpp
  instruction/SkipIfEqRegisterInstructionTest.cpp
  instruction/SkipIfEqValueInstructionTest.cpp
  instruction/SkipIfNeValueInstructionTest.cpp
  instruction/SubnInstructionTest.cpp
  instruction/SubRegisterInstructionTest.cpp

  memory/FixedMemoryTest.cpp
)

add_executable(chiptests ${SOURCES})

target_link_libraries(chiptests PRIVATE
  GTest::gtest_main
  libchip8
)

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
