#include "SemanticException.h"

using namespace std;

namespace chip8 {

  
SemanticException::SemanticException(int line, int col, const string& what)
    : Exception(what),
      line_(line),
      column_(col),
      include_postion_(true)
{}


SemanticException::SemanticException(const string& what) 
    : Exception(what),
      include_postion_(false)
{}


ostream& operator<<(ostream& out, const SemanticException& ex) {
  if (ex.include_postion_) {
    out << "SemanticException: " << ex.what_ <<  " at " 
      << ex.line_ << ':' << ex.column_;
  } else {
    out << "SemanticException: " << ex.what_;
  }
  return out;
}


} // namespace chip8
