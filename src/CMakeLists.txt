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

  instruction/AddValueInstruction.cpp
  instruction/CallInstruction.cpp
  instruction/ClearDisplayInstruction.cpp
  instruction/ExecutionContext.cpp
  instruction/Instruction.cpp
  instruction/JumpInstruction.cpp
  instruction/LoadRegisterInstruction.cpp
  instruction/LoadValueInstruction.cpp
  instruction/ReturnInstruction.cpp
  instruction/SkipIfEqRegisterInstruction.cpp
  instruction/SkipIfEqValueInstruction.cpp
  instruction/SkipIfNeValueInstruction.cpp
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
