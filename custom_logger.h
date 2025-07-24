/*
 * @Author: lenomirei lenomirei@163.com
 * @Date: 2025-07-24 15:41:46
 * @LastEditors: lenomirei lenomirei@163.com
 * @LastEditTime: 2025-07-24 18:16:24
 * @FilePath: \SpdlogWrapper\custom_logger.h
 * @Description: 
 * 
 */
#include <filesystem>
#include <string>
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

namespace common {

static spdlog::level::level_enum g_log_level = spdlog::level::DEFAULT_SDK_LOG_LEVEL;

class CustomNSLogger {
 public:
  enum class LogLevel {
    trace,
    debug,
    info,
    warn,
    error,
    fatal
  };

  static void InitDefaultLogger(const std::filesystem::path& log_path, size_t log_file_size, size_t max_file_count) {
    if (default_logger_)
      return;

    try {
      auto logger = spdlog::get(DEFAULT_LOGGER_NAME);
      if (logger) {
        default_logger_ = logger;
        return;
      }

      default_logger_ = spdlog::rotating_logger_mt(DEFAULT_LOGGER_NAME, log_path, log_file_size, max_file_count);
      default_logger_->set_level(g_log_level);
      default_logger_->flush_on(g_log_level);
      default_logger_->set_pattern("[%m-%d %H:%M:%S.%e] [%^%l%$] [%s] [%!] [line:%#] [thread %t] %v");
    } catch (const std::exception& e) {
    }
  }

  template <typename... ArgList>
  static void logger_trace(const std::string& logger_name, const std::string& format_print_str, const ArgList&... args) {
    SPDLOG_LOGGER_TRACE(spdlog::get(logger_name), format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void trace(const std::string& format_print_str, const ArgList&... args) {
    if (default_logger_)
      SPDLOG_LOGGER_TRACE(default_logger_, format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_debug(const std::string& logger_name, const std::string& format_print_str, const ArgList&... args) {
    SPDLOG_LOGGER_DEBUG(spdlog::get(logger_name), format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void debug(const std::string& format_print_str, const ArgList&... args) {
    if (default_logger_)
      SPDLOG_LOGGER_DEBUG(default_logger_, format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_info(const std::string& logger_name, const std::string& format_print_str, const ArgList&... args) {
    SPDLOG_LOGGER_INFO(spdlog::get(logger_name), format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void info(const std::string& format_print_str, const ArgList&... args) {
    if (default_logger_)
      SPDLOG_LOGGER_INFO(default_logger_, format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_warn(const std::string& logger_name, const std::string& format_print_str, const ArgList&... args) {
    SPDLOG_LOGGER_WARN(spdlog::get(logger_name), format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void warn(const std::string& format_print_str, const ArgList&... args) {
    if (default_logger_)
      SPDLOG_LOGGER_WARN(default_logger_, format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_error(const std::string& logger_name, const std::string& format_print_str, const ArgList&... args) {
    SPDLOG_LOGGER_ERROR(spdlog::get(logger_name), format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void error(const std::string& format_print_str, const ArgList&... args) {
    if (default_logger_)
      SPDLOG_LOGGER_ERROR(default_logger_, format_print_str, std::forward<ArgList>(args)...);
  }

  static std::shared_ptr<spdlog::logger> default_logger_;
};

std::shared_ptr<spdlog::logger> CustomNSLogger::default_logger_ = nullptr;

}  // namespace common