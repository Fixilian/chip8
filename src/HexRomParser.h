#ifndef CHIP8_HEXROMPARSER_H
#define CHIP8_HEXROMPARSER_H

#include <string>
#include <vector>
#include <unordered_set>

#include "Aliases.h"
#include "Parser.h"

namespace chip8 {

/**
 * Hexadecimal ROM parser.
 * It ignores any whitespace or line break.
 * It ignores also tabs, in order to ignore any kind of whitespace.
 * It allows comments in hexadecimal ROM files 
 * to make it easier to people to know what code snippets should do.
 */
class HexRomParser : public Parser {
 public:
  /**
   * @param text - hexadecimal ROM.
   */
  HexRomParser(std::string_view text);

  HexRomParser(const HexRomParser&) = delete;
  HexRomParser& operator=(const HexRomParser&) = delete;
  HexRomParser(HexRomParser&&) = delete;
  HexRomParser& operator=(HexRomParser&&) = delete;

  /**
   * Returns next opcode from hexadecimal ROM.
   * After Syntax error behavior is undefined.
   * @returns next opcode or 0 if ROM is ended.
   * @throws SyntaxException when ROM contains unexpected characters. 
   */
  word next();
  
  /**
   * Returns line in ROM of previous opcode (of next() result).
   * @returns line in ROM of previous opcode.
   */
  int getLine() { return opcode_line_; }

  /**
   * Returns column in ROM of previous opcode (of next() result).
   * @returns column in ROM of previous opcode.
   */
  int getColumn() { return opcode_col_; }

 private:
  static std::unordered_set<char> alphabet;
  std::string_view text_;
  std::size_t pos_;
  int opcode_line_;
  int opcode_col_;
  int line_;
  int col_;

  bool isWhitespace(char ch);

  word charToDigit(char ch);

  word charWordToWord(const std::vector<char>& cword);

  void skipOneLineComment();

  void skipMultiLineComment();
};

} // namespace chip8

#endif // CHIP8_HEXROMPARSER_H
