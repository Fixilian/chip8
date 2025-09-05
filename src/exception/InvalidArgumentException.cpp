#include "InvalidArgumentException.h"

using namespace std;

namespace chip8 {


InvalidArgumentException::InvalidArgumentException(const string& what)
    : Exception(what)
{}


ostream& operator<< (ostream& out, const InvalidArgumentException& ex) {
  out << "InvalidArgumentException: " << ex.what_ << '\n';
  return out;
}


} // namespace chip8
