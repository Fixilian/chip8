#ifndef CHIP8_BASE_THREADREGISTRY_H
#define CHIP8_BASE_THREADREGISTRY_H

#include <string>

namespace chip8 {

class ThreadRegistry {
 public:
  static void setThreadName(const std::string& name);

  static const std::string& getThreadName();

 private:
  static thread_local std::string name_;
};

} // namespace chip8

#endif // CHIP8_BASE_THREADREGISTRY_H
