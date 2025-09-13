#ifndef CHIP8_EXCEPTION_IOEXCEPTION_H
#define CHIP8_EXCEPTION_IOEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class IOException : public Exception {
 public:
  IOException(const std::string& what);

  IOException(const IOException&) = default;
  IOException& operator=(const IOException&) = default;
  IOException(IOException&&) = default;
  IOException& operator=(IOException&&) = default;

  friend std::ostream& operator<<(std::ostream& out, 
                                    const IOException& ex);
};

std::ostream& operator<<(std::ostream& out, const IOException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_IOEXCEPTION_H
