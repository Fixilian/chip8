#ifndef CHIP8_EXCEPTION_UNKNOWNKEYEXCEPTION_H
#define CHIP8_EXCEPTION_UNKNOWNKEYEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class UnknownKeyException : public Exception {
 public:
  UnknownKeyException(int key, const std::string& what);

  UnknownKeyException(const UnknownKeyException&) = default;
  UnknownKeyException& operator=(const UnknownKeyException&) = default;
  UnknownKeyException(UnknownKeyException&&) = default;
  UnknownKeyException& operator=(UnknownKeyException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, const UnknownKeyException& ex);

 private:
  int key_;
};

std::ostream& operator<< (std::ostream& out, const UnknownKeyException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_UNKNOWNKEYEXCEPTION_H