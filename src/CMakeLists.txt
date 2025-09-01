set(SOURCES
  base/BitOperations.cpp
  base/Rom.cpp

  compiler/Compiler.cpp
  compiler/HexRomParser.cpp
  compiler/RomBuilder.cpp

  exception/Exception.cpp
  exception/OutOfRangeException.cpp
  exception/SegFaultException.cpp
  exception/SemanticException.cpp
  exception/SyntaxException.cpp

  graphics/Frame.cpp
  graphics/MonochromeDisplay.cpp

  instruction/AddRegisterInstruction.cpp
  instruction/AddValueInstruction.cpp
  instruction/BitwiseAndInstruction.cpp
  instruction/BitwiseOrInstruction.cpp
  instruction/BitwiseXorInstruction.cpp
  instruction/CallInstruction.cpp
  instruction/ClearDisplayInstruction.cpp
  instruction/ExecutionContext.cpp
  instruction/Instruction.cpp
  instruction/JumpInstruction.cpp
  instruction/JumpWithOffsetInstruction.cpp
  instruction/LoadIRegisterInstruction.cpp
  instruction/LoadRegisterInstruction.cpp
  instruction/LoadValueInstruction.cpp
  instruction/RandomInstruction.cpp
  instruction/ReturnInstruction.cpp
  instruction/ShiftLeftInstruction.cpp
  instruction/ShiftRightInstruction.cpp
  instruction/SkipIfEqRegisterInstruction.cpp
  instruction/SkipIfEqValueInstruction.cpp
  instruction/SkipIfNeRegisterInstruction.cpp
  instruction/SkipIfNeValueInstruction.cpp
  instruction/SubnInstruction.cpp
  instruction/SubRegisterInstruction.cpp
  instruction/SysJumpInstruction.cpp

  memory/FixedMemory.cpp
)

add_library(libchip8 ${SOURCES})

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
  -Wold-style-cast
  -Woverloaded-virtual
  -Wredundant-decls
  -Wsign-promo
)
