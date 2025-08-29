#ifndef CHIP8_EXCEPTION_SEGFAULTEXCEPTION_H
#define CHIP8_EXCEPTION_SEGFAULTEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class SegFaultException : public Exception {
 public:
  SegFaultException(const std::string& what);

  SegFaultException(const SegFaultException&) = default;
  SegFaultException& operator=(const SegFaultException&) = default;
  SegFaultException(SegFaultException&&) = default;
  SegFaultException& operator=(SegFaultException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, 
                                    const SegFaultException& ex);
};

std::ostream& operator<< (std::ostream& out, const SegFaultException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_SEGFAULTEXCEPTION_H
