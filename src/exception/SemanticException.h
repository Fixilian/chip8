#ifndef CHIP8_EXCEPTION_SEMANTICEXCEPTION_H
#define CHIP8_EXCEPTION_SEMANTICEXCEPTION_H

#include <ostream>
#include <string>

#include "Exception.h"

namespace chip8 {

class SemanticException : public Exception {
 public:
  SemanticException(int line, int col, const std::string& what);
  SemanticException(const std::string& what);

  SemanticException(const SemanticException&) = default;
  SemanticException& operator=(const SemanticException&) = default;
  SemanticException(SemanticException&&) = default;
  SemanticException& operator=(SemanticException&&) = default;

  friend std::ostream& operator<< (std::ostream& out, const SemanticException& ex);

 private:
  int line_;
  int column_;
  bool include_postion_;
};

std::ostream& operator<< (std::ostream& out, const SemanticException& ex);

} // namespace chip8

#endif // CHIP8_EXCEPTION_SEMANTICEXCEPTION_H
