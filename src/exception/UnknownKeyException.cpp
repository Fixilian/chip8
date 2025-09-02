#include "UnknownKeyException.h"

using namespace std;

namespace chip8 {

  
UnknownKeyException::UnknownKeyException(int key, const string& what)
    : Exception(what),
      key_(key) 
{}


ostream& operator<< (ostream& out, const UnknownKeyException& ex) {
  out << "UnknownKeyException: " << ex.what_ <<  ", key = " << ex.key_ << '\n';
  return out;
}


} // namespace chip8
