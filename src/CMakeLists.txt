set(SOURCES
  base/BitOperations.cpp
  base/Rom.cpp
  base/RomView.cpp

  compiler/Compiler.cpp
  compiler/HexRomParser.cpp
  compiler/RomBuilder.cpp

  exception/Exception.cpp
  exception/OutOfRangeException.cpp
  exception/SemanticException.cpp
  exception/SyntaxException.cpp

  graphics/Frame.cpp
  graphics/MonochromeDisplay.cpp
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
