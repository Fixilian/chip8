#include "InvalidConfigException.h"

using namespace std;

namespace chip8 {


InvalidConfigException::InvalidConfigException(const string& what)
    : Exception(what)
{}


ostream& operator<<(ostream& out, const InvalidConfigException& ex) {
  out << "InvalidConfigException: " << ex.what_;
  return out;
}


} // namespace chip8
