#include "Log.h"

#include <iostream>
#include <memory>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include "base/ThreadRegistry.h"

#undef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

using namespace std;

namespace chip8 {


class ThreadNameFormatterFlag : public spdlog::custom_flag_formatter {
 public:
  void format(
    const spdlog::details::log_msg &, 
    const tm &, 
    spdlog::memory_buf_t &dest) override 
  {
    auto thread_name = ThreadRegistry::getThreadName();
    dest.append(thread_name.data(), thread_name.data() + thread_name.size());
  }

  unique_ptr<custom_flag_formatter> clone() const override {
    return spdlog::details::make_unique<ThreadNameFormatterFlag>();
  }
};


bool Log::init(bool enable_console) {
  try {
    auto formatter = make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<ThreadNameFormatterFlag>('*');
    formatter->set_pattern("[%^%=7l%$] [%*] %v");
    spdlog::set_formatter(std::move(formatter));
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
    case LogLevel::Trace: spdlog::set_level(spdlog::level::trace); break;
    case LogLevel::Debug: spdlog::set_level(spdlog::level::debug); break;
    case LogLevel::Info: spdlog::set_level(spdlog::level::info); break;
    case LogLevel::Warn: spdlog::set_level(spdlog::level::warn); break;
    case LogLevel::Error: spdlog::set_level(spdlog::level::err); break;
    default:  break;
  }
}


void Log::trace(const char* s) {
  spdlog::trace(s);
}


void Log::trace(const std::string& s) {
  trace(s.c_str());
}


void Log::debug(const char* s) {
  spdlog::debug(s);
}


void Log::debug(const std::string& s) {
  debug(s.c_str());
}


void Log::info(const char* s) {
  spdlog::info(s);
}


void Log::info(const std::string& s) {
  info(s.c_str());
}


void Log::warn(const char* s) {
  spdlog::warn(s);
}


void Log::warn(const std::string& s) {
  warn(s.c_str());
}


void Log::error(const char* s) {
  spdlog::error(s);
}

void Log::error(const std::string& s) {
  error(s.c_str());
}


} // namespace chip8
