#ifndef CHIP8_EXCEPTION_OUTOFRANGEEXCEPTION_H
#define CHIP8_EXCEPTION_OUTOFRANGEEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class OutOfRangeException : public Exception {
 public:
  OutOfRangeException(const std::string& what);

  OutOfRangeException(const OutOfRangeException&) = default;
  OutOfRangeException& operator=(const OutOfRangeException&) = default;
  OutOfRangeException(OutOfRangeException&&) = default;
  OutOfRangeException& operator=(OutOfRangeException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, 
                                    const OutOfRangeException& ex);
};

std::ostream& operator<< (std::ostream& out, const OutOfRangeException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_OUTOFRANGEEXCEPTION_H
