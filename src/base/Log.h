#ifndef CHIP8_BASE_LOG_H
#define CHIP8_BASE_LOG_H

#include <spdlog/spdlog.h>
#include <string>

namespace chip8 {

enum class LogLevel {
  Trace,
  Debug,
  Info,
  Warn,
  Error
};

class Log {
 public:
  static bool init(bool enable_console);

  static void setLevel(LogLevel level);

  static void trace(const char* s);
  static void trace(const std::string& s);

  template <typename... Args>
  static void trace(const char* fmt, Args &&...args) {
    spdlog::trace(fmt::runtime(fmt), std::forward<Args>(args)...);
  }

  static void debug(const char* s);
  static void debug(const std::string& s);

  template <typename... Args>
  static void debug(const char* fmt, Args &&...args){
    spdlog::debug(fmt::runtime(fmt), std::forward<Args>(args)...);
  }

  static void info(const char* s);
  static void info(const std::string& s);

  template <typename... Args>
  static void info(const char* fmt, Args &&...args){
    spdlog::info(fmt::runtime(fmt), std::forward<Args>(args)...);
  }

  static void warn(const char* s);
  static void warn(const std::string& s);

  template <typename... Args>
  static void warn(const char* fmt, Args &&...args){
    spdlog::warn(fmt::runtime(fmt), std::forward<Args>(args)...);
  }

  static void error(const char* s);
  static void error(const std::string& s);

  template <typename... Args>
  static void error(const char* fmt, Args &&...args){
    spdlog::error(fmt::runtime(fmt), std::forward<Args>(args)...);
  }
};

} // namespace chip8

#endif // CHIP8_BASE_LOG_H
