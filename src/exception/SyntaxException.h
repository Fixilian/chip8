#ifndef CHIP8_EXCEPTION_SYNTAXEXCEPTION_H
#define CHIP8_EXCEPTION_SYNTAXEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class SyntaxException : public Exception {
 public:
  SyntaxException(int line, int col, const std::string& what);

  SyntaxException(const SyntaxException&) = default;
  SyntaxException& operator=(const SyntaxException&) = default;
  SyntaxException(SyntaxException&&) = default;
  SyntaxException& operator=(SyntaxException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, const SyntaxException& ex);

 private:
  int line_;
  int column_;
};

std::ostream& operator<< (std::ostream& out, const SyntaxException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_SYNTAXEXCEPTION_H
