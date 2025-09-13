#include "IOException.h"

using namespace std;

namespace chip8 {


IOException::IOException(const string& what)
    : Exception(what)
{}


ostream& operator<<(ostream& out, const IOException& ex) {
  out << "IOException: " << ex.what_;
  return out;
}


} // namespace chip8
