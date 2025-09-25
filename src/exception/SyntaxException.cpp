#include "SyntaxException.h"

using namespace std;

namespace chip8 {

  
SyntaxException::SyntaxException(int line, int col, const string& what)
    : Exception(what),
      line_(line),
      column_(col) 
{}


ostream& operator<<(ostream& out, const SyntaxException& ex) {
  out << "SyntaxException: " << ex.what_ <<  " at " 
    << ex.line_ << ':' << ex.column_;
  return out;
}


} // namespace chip8
