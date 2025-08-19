#include "Exception.h"

using namespace std;

namespace chip8 {


Exception::Exception(const string& what)
    : what_(what)
{}


ostream& operator<< (ostream& out, const Exception& ex) {
  out << ex.what_ << '\n';
  return out;
}


} // namespace chip8
