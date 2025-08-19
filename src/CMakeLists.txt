set(SOURCES
  base/BitOperations.cpp

  exception/Exception.cpp
  exception/OutOfRangeException.cpp
  exception/SemanticException.cpp
  exception/SyntaxException.cpp

  HexRomParser.cpp
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
