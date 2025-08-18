#include "SyntaxError.h"

namespace chip8 {

  
SyntaxError::SyntaxError(int line, int col, const std::string& message)
    : message_(message),
      line_(line),
      column_(col) 
{}


std::ostream& operator<< (std::ostream& stream, const SyntaxError& err) {
  stream << "Syntax error: " << err.message_ <<  " at " 
    << err.line_ << ':' << err.column_;
  return stream;
}

} // namespace chip8
