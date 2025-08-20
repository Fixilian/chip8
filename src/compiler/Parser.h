#ifndef CHIP8_COMPILER_PARSER_H
#define CHIP8_COMPILER_PARSER_H

#include "base/Aliases.h"

namespace chip8 {

/**
 * ROM parser interface. 
 */
class Parser {
 public:
  virtual ~Parser() {}

  /**
   * Returns next opcode from ROM.
   * @returns next opcode or 0 if ROM is ended.
   */
  virtual word next() = 0;
  
  /**
   * Returns line in ROM of previous opcode (of next() result).
   * @returns line in ROM of previous opcode.
   */
  virtual int getLine() = 0;

  /**
   * Returns column in ROM of previous opcode (of next() result).
   * @returns column in ROM of previous opcode.
   */
  virtual int getColumn() = 0;
};

}

#endif // CHIP8_COMPILER_PARSER_H
