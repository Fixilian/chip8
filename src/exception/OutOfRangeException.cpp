#include "OutOfRangeException.h"

using namespace std;

namespace chip8 {


OutOfRangeException::OutOfRangeException(const string& what)
    : Exception(what)
{}


ostream& operator<< (ostream& out, const OutOfRangeException& ex) {
  out << "OutOfRangeException: " << ex.what_ << '\n';
  return out;
}


} // namespace chip8
