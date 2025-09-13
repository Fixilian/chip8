#include "Exception.h"

#include <sstream>

using namespace std;

namespace chip8 {


Exception::Exception(const string& what)
    : what_(what)
{}


const char* Exception::what() const noexcept {
  return what_.c_str();
}


string Exception::message() const {
  stringstream ss;
  ss << *this;
  return ss.str();
}


ostream& operator<<(ostream& out, const Exception& ex) {
  out << ex.what_;
  return out;
}


} // namespace chip8
