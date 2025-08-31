set(SOURCES
  base/BitOperationsTest.cpp
  base/StackTest.cpp
  
  compiler/CompilerTest.cpp
  compiler/HexRomParserTest.cpp
  compiler/RomBuilderTest.cpp

  graphics/FrameTest.cpp

  instruction/CallInstructionTest.cpp
  instruction/ClearDisplayInstructionTest.cpp
  instruction/JumpInstructionTest.cpp
  instruction/ReturnInstructionTest.cpp
  instruction/SkipIfEqRegisterInstructionTest.cpp
  instruction/SkipIfEqValueInstructionTest.cpp
  instruction/SkipIfNeValueInstructionTest.cpp

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
