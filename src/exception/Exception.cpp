#include "Exception.h"

using namespace std;

namespace chip8 {


Exception::Exception(const string& what)
    : what_(what)
{}


const char* Exception::what() const noexcept {
  return what_.c_str();
}


ostream& operator<< (ostream& out, const Exception& ex) {
  out << ex.what_ << '\n';
  return out;
}


} // namespace chip8
