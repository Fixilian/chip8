#include "OutOfRangeException.h"

using namespace std;

namespace chip8 {


OutOfRangeException::OutOfRangeException(const string& what)
    : Exception(what)
{}


} // namespace chip8
