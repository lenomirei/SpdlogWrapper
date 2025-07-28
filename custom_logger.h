/*
 * @Author: lenomirei lenomirei@163.com
 * @Date: 2025-07-24 15:41:46
 * @LastEditors: lenomirei lenomirei@163.com
 * @LastEditTime: 2025-07-28 16:37:07
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

class CustomLogger {
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
  static void logger_trace(const spdlog::source_loc& loc, const std::string& logger_name, const std::string& format_print_str, ArgList&&... args) {
    auto logger = spdlog::get(logger_name);
    if (logger)
      logger->log(loc, spdlog::level::trace , format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void trace(const spdlog::source_loc& loc, const std::string& format_print_str, ArgList&&... args) {
    if (default_logger_)
      default_logger_->log(loc, spdlog::level::trace , format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_debug(const spdlog::source_loc& loc, const std::string& logger_name, const std::string& format_print_str, ArgList&&... args) {
    auto logger = spdlog::get(logger_name);
    if (logger)
      logger->log(loc, spdlog::level::debug , format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void debug(const spdlog::source_loc& loc, const std::string& format_print_str, ArgList&&... args) {
    if (default_logger_)
      default_logger_->log(loc, spdlog::level::debug , format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_info(const spdlog::source_loc& loc, const std::string& logger_name, const std::string& format_print_str, ArgList&&... args) {
    auto logger = spdlog::get(logger_name);
    if (logger)
      logger->log(loc, spdlog::level::info , format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void info(const spdlog::source_loc& loc, const std::string& format_print_str, ArgList&&... args) {
    if (default_logger_)
      default_logger_->log(loc, spdlog::level::info , format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_warn(const spdlog::source_loc& loc, const std::string& logger_name, const std::string& format_print_str, ArgList&&... args) {
    auto logger = spdlog::get(logger_name);
    if (logger)
      logger->log(loc, spdlog::level::warn , format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void warn(const spdlog::source_loc& loc, const std::string& format_print_str, ArgList&&... args) {
    if (default_logger_)
      default_logger_->log(loc, spdlog::level::warn , format_print_str, std::forward<ArgList>(args)...);
  }

  template <typename... ArgList>
  static void logger_error(const spdlog::source_loc& loc, const std::string& logger_name, const std::string& format_print_str, ArgList&&... args) {
    auto logger = spdlog::get(logger_name);
    if (logger)
      logger->log(loc, spdlog::level::err , format_print_str, std::forward<ArgList>(args)...);
  }
  template <typename... ArgList>
  static void error(const spdlog::source_loc& loc, const std::string& format_print_str, ArgList&&... args) {
    if (default_logger_)
      default_logger_->log(loc, spdlog::level::err , format_print_str, std::forward<ArgList>(args)...);
  }

  inline static std::shared_ptr<spdlog::logger> default_logger_ = nullptr;
};  // class CustomLogger

}  // namespace common

#define CUSTOMLOGGER_LOGGER_TRACE(logger_name, fmt, ...) \
  common::CustomLogger::logger_trace(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, logger_name, fmt, ##__VA_ARGS__)
#define CUSTOMLOGGER_TRACE(fmt, ...) \
  common::CustomLogger::trace(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt, ##__VA_ARGS__)

#define CUSTOMLOGGER_LOGGER_DEBUG(logger_name, fmt, ...) \
  common::CustomLogger::logger_debug(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, logger_name, fmt, ##__VA_ARGS__)
#define CUSTOMLOGGER_DEBUG(fmt, ...) \
  common::CustomLogger::debug(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt, ##__VA_ARGS__)

#define CUSTOMLOGGER_LOGGER_INFO(logger_name, fmt, ...) \
  common::CustomLogger::logger_info(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, logger_name, fmt, ##__VA_ARGS__)
#define CUSTOMLOGGER_INFO(fmt, ...) \
  common::CustomLogger::info(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt, ##__VA_ARGS__)

#define CUSTOMLOGGER_LOGGER_WARN(logger_name, fmt, ...) \
  common::CustomLogger::logger_warn(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, logger_name, fmt, ##__VA_ARGS__)
#define CUSTOMLOGGER_WARN(fmt, ...) \
  common::CustomLogger::warn(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt, ##__VA_ARGS__)

#define CUSTOMLOGGER_LOGGER_ERROR(logger_name, fmt, ...) \
  common::CustomLogger::logger_error(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, logger_name, fmt, ##__VA_ARGS__)
#define CUSTOMLOGGER_ERROR(fmt, ...) \
  common::CustomLogger::error(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt, ##__VA_ARGS__)