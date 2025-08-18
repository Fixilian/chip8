#include "HexRomParser.h"

#include "SyntaxError.h"

using namespace std;

namespace chip8 {


unordered_set<char> HexRomParser::alphabet = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'a', 'b', 'c', 'd', 'e', 'f',
  'A', 'B', 'C', 'D', 'E', 'F'};


HexRomParser::HexRomParser(string_view text) 
    : text_(text),
      pos_(0),
      opcode_line_(0),
      opcode_col_(0),
      line_(1),
      col_(0)
{}


word HexRomParser::next() {
  const size_t kCharWordSize = 4;
  vector<char> cword(kCharWordSize);
  size_t cword_len = 0;

  for (; pos_ < text_.length(); pos_ += 1) {
    col_ += 1;
    char ch = text_[pos_];

    if (isWhitespace(ch)) {
      continue;
    }

    if (ch == '\n') {
      line_ += 1;
      col_ = 0;
      continue;
    }

    if (alphabet.contains(ch)) {
      if (cword_len == 0) {
        opcode_line_ = line_;
        opcode_col_ = col_;
      }
      cword[cword_len] = ch;
      cword_len += 1;
      if (cword_len == kCharWordSize) {
        break;
      }
      continue;
    }

    if (ch == '/' && pos_ + 1 < text_.length()) {
      if (text_[pos_ + 1] == '/') {
        pos_ += 2; // move to next char after "//"
        skipOneLineComment();
        continue;
      }
      if (text_[pos_ + 1] == '*') {
        pos_ += 2; // move to next char after "/*"
        skipMultiLineComment();
        continue;
      }
    }

    throw SyntaxError(line_, col_, "Unexpected character");
  }

  if (cword_len != 0 && cword_len != kCharWordSize) {
    throw SyntaxError(line_, col_, "Unexpected characters at the end");
  }
  
  pos_ += 1;
  if (cword_len == kCharWordSize) {
    return charWordToWord(cword);
  } else {
    return 0;
  }
}


bool HexRomParser::isWhitespace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\r';
}


word HexRomParser::charToDigit(char ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  }
  if (ch >= 'a' && ch <= 'z') {
    return ch - 'a' + 10;
  }
  return ch - 'A' + 10;
}


word HexRomParser::charWordToWord(const std::vector<char>& cword) {
  const size_t kHexDigitSizeInBits = 4;
  word result = 0;
  for (size_t i = 0; i < cword.size(); i += 1) {
    word digit = charToDigit(cword[i]);
    size_t shift = (cword.size() - 1 - i) * kHexDigitSizeInBits;
    result |= (digit << shift);
  }
  return result;
}

void HexRomParser::skipOneLineComment() {
  while (pos_ < text_.length() && text_[pos_] != '\n') {
    pos_ += 1;
  }
  line_ += 1;
  col_ = 0;
}

void HexRomParser::skipMultiLineComment() {
  while (pos_ + 1 < text_.length() && 
          !(text_[pos_] == '*' && text_[pos_ + 1] == '/')) {
    pos_ += 1;
    col_ += 1;
    if (text_[pos_] == '\n') {
      line_ += 1;
      col_ = 0;
    }
  }

  if (pos_ + 1 >= text_.length()) {
    throw SyntaxError(line_, col_, "Incorrect end of multiline comment");
  }

  pos_ += 2; // move to next char after "*/"
}

} // namespace chip8
