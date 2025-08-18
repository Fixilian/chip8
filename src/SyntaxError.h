#ifndef CHIP8_SYNTAXERROR_H
#define CHIP8_SYNTAXERROR_H

#include <ostream>
#include <string>

namespace chip8 {

class SyntaxError {
 public:
  SyntaxError(int line, int col, const std::string& message);

  SyntaxError(const SyntaxError&) = default;
  SyntaxError& operator=(const SyntaxError&) = default;
  SyntaxError(SyntaxError&&) = default;
  SyntaxError& operator=(SyntaxError&&) = default;

  friend std::ostream& operator<< (std::ostream& stream, const SyntaxError& err);

 private:
  std::string message_;
  int line_;
  int column_;
};

std::ostream& operator<< (std::ostream& stream, const SyntaxError& err);

} // namespace chip8

#endif // CHIP8_SYNTAXERROR_H
