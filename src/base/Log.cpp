#include "Log.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

using namespace std;

namespace chip8 {


bool Log::init(bool enable_console) {
  try {
    spdlog::set_pattern("[%^%=7l%$] [t %t] %v");
    if (enable_console) {
      spdlog::stdout_logger_mt("console_log"); 
    }
    spdlog::basic_logger_mt("file_log", "log.txt"); 
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log init failed: " << ex.what() << '\n';
    return false;
  }
  return true;
}


void Log::setLevel(LogLevel level) {
  switch (level) {
    case LogLevel::Debug: spdlog::set_level(spdlog::level::debug); break;
    case LogLevel::Info: spdlog::set_level(spdlog::level::info); break;
    case LogLevel::Warn: spdlog::set_level(spdlog::level::warn); break;
    case LogLevel::Error: spdlog::set_level(spdlog::level::err); break;
    default:  break;
  }
}


void Log::debug(const char* s) {
  SPDLOG_DEBUG(s);
}


void Log::debug(const std::string& s) {
  debug(s.c_str());
}


void Log::debug(const char* s, const char* arg) {
  spdlog::debug(fmt::runtime(s), arg);
}


void Log::info(const char* s) {
  spdlog::info(s);
}


void Log::info(const std::string& s) {
  info(s.c_str());
}


void Log::info(const char* s, const char* arg) {
  spdlog::info(fmt::runtime(s), arg);
}


void Log::warn(const char* s) {
  spdlog::warn(s);
}


void Log::warn(const std::string& s) {
  warn(s.c_str());
}


void Log::warn(const char* s, const char* arg) {
  spdlog::warn(fmt::runtime(s), arg);
}


void Log::error(const char* s) {
  spdlog::error(s);
}

void Log::error(const std::string& s) {
  error(s.c_str());
}


void Log::error(const char* s, const char* arg) {
  spdlog::error(fmt::runtime(s), arg);
}


} // namespace chip8
