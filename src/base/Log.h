#ifndef CHIP8_BASE_LOG_H
#define CHIP8_BASE_LOG_H

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
  static void trace(const char* s, const char* arg);

  static void debug(const char* s);
  static void debug(const std::string& s);
  static void debug(const char* s, const char* arg);

  static void info(const char* s);
  static void info(const std::string& s);
  static void info(const char* s, const char* arg);

  static void warn(const char* s);
  static void warn(const std::string& s);
  static void warn(const char* s, const char* arg);

  static void error(const char* s);
  static void error(const std::string& s);
  static void error(const char* s, const char* arg);
};

} // namespace chip8

#endif // CHIP8_BASE_LOG_H
