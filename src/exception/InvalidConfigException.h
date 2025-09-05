#ifndef CHIP8_EXCEPTION_INVALIDCONFIGEXCEPTION_H
#define CHIP8_EXCEPTION_INVALIDCONFIGEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class InvalidConfigException : public Exception {
 public:
  InvalidConfigException(const std::string& what);

  InvalidConfigException(const InvalidConfigException&) = default;
  InvalidConfigException& operator=(const InvalidConfigException&) = default;
  InvalidConfigException(InvalidConfigException&&) = default;
  InvalidConfigException& operator=(InvalidConfigException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, 
                                    const InvalidConfigException& ex);
};

std::ostream& operator<< (std::ostream& out, const InvalidConfigException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_INVALIDCONFIGEXCEPTION_H
