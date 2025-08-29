#include "SegFaultException.h"

using namespace std;

namespace chip8 {


SegFaultException::SegFaultException(const string& what)
    : Exception(what)
{}


ostream& operator<< (ostream& out, const SegFaultException& ex) {
  out << "SegFaultException: " << ex.what_ << '\n';
  return out;
}


} // namespace chip8
