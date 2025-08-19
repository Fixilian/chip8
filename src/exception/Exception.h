#ifndef CHIP8_EXCEPTION_EXCEPTION_H
#define CHIP8_EXCEPTION_EXCEPTION_H

#include <ostream>
#include <string>

namespace chip8 {

class Exception {
 public:
  Exception(const std::string& what);

  Exception(const Exception&) = default;
  Exception& operator=(const Exception&) = default;
  Exception(Exception&&) = default;
  Exception& operator=(Exception&&) = default;

  friend std::ostream& operator<< (std::ostream& out, const Exception& ex);

 protected:
  std::string what_;
};

std::ostream& operator<< (std::ostream& out, const Exception& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_EXCEPTION_H
