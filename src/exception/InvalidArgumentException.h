#ifndef CHIP8_EXCEPTION_INVALIDARGUMENTEXCEPTION_H
#define CHIP8_EXCEPTION_INVALIDARGUMENTEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class InvalidArgumentException : public Exception {
 public:
  InvalidArgumentException(const std::string& what);

  InvalidArgumentException(const InvalidArgumentException&) = default;
  InvalidArgumentException& operator=(const InvalidArgumentException&) = default;
  InvalidArgumentException(InvalidArgumentException&&) = default;
  InvalidArgumentException& operator=(InvalidArgumentException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, 
                                    const InvalidArgumentException& ex);
};

std::ostream& operator<< (std::ostream& out, const InvalidArgumentException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_INVALIDARGUMENTEXCEPTION_H
