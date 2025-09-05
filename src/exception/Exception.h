#ifndef CHIP8_EXCEPTION_EXCEPTION_H
#define CHIP8_EXCEPTION_EXCEPTION_H

#include <exception>
#include <ostream>
#include <string>

namespace chip8 {

class Exception : public std::exception {
 public:
  Exception(const std::string& what);

  virtual ~Exception() {}

  Exception(const Exception&) = default;
  Exception& operator=(const Exception&) = default;
  Exception(Exception&&) = default;
  Exception& operator=(Exception&&) = default;

  virtual const char* what() const noexcept override;

  friend std::ostream& operator<< (std::ostream& out, const Exception& ex);

 protected:
  std::string what_;
};

std::ostream& operator<< (std::ostream& out, const Exception& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_EXCEPTION_H
