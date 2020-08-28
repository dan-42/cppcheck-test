///
/// This is the internal log header for STUDIO
/// DO NOT INCLUDE use log.hpp

/// Copyright (C) Nanosurf AG - All Rights Reserved (2017)
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential
/// https://www.nanosurf.com
///
#pragma once
#ifndef MY_STD_UTIL_LOG_STUDIO_HPP
#define MY_STD_UTIL_LOG_STUDIO_HPP

#include <fmt/format.h>

#include <string>
#include <sstream>

namespace foobar
{


// Forward declaration
struct log_configuration_v3{};
using log_configuration = log_configuration_v3;

///
///
///
enum class log_level
{
  log_trace,
  log_debug,
  log_info,
  log_warn,
  log_error,
  log_critical,
  log_off
};

///
///
///
//using log_channel_type = const char*;
using log_channel_type = std::string;

///
///
///
using log_message_type = std::string;


///
/// ???
///
auto log_setup(const log_configuration& config) -> void;

///
/// ???
///
auto log(log_level level, log_channel_type channel, const log_message_type& msg) -> void;

///
/// ???
///
auto log_user_marker() -> void;

///
/// ???
///
auto log_level_to_string(log_level level) -> std::string;


} //namespace foobar


  ///
  /// The guts of the good old stream logging macros
  /// use as in MobileS  MYLOG_DEBUG("some channel", "Hello " << 42)
  ///
#define MYLOG_INTERNAL_STREAM(CHANNEL, LEVEL, STREAM)                                                            \
  {                                                                                                               \
    std::stringstream ss;                                                                                         \
    ss << STREAM;                                                                                                 \
    constexpr auto level = ::foobar::log_level::LEVEL;                                            \
    ::foobar::log(level, CHANNEL, ss.str());                                                      \
  }                                                                                                               \

  ///
  /// The guts of a fmt formatted string,
  /// Use as MYLOG_DEBUGF("some channel", "{} {}", "Hello", 42)
  ///
#define MYLOG_INTERNAL_FMT_STR(CHANNEL, LEVEL, FMT_STR, ...)                                                     \
  {                                                                                                               \
    constexpr auto level = ::foobar::log_level::LEVEL;                                            \
    ::foobar::log(level, CHANNEL, fmt::format(FMT_STR, __VA_ARGS__));                             \
  }                                                                                                               \


///
/// Default logging macros
///
#define MYLOG(CHANNEL, LEVEL, STREAM)                                                                           \
  MYLOG_INTERNAL_STREAM(CHANNEL, LEVEL, STREAM)

#define MYLOG_DEBUG(CHANNEL, STREAM)                                                                             \
  MYLOG((CHANNEL), log_debug, STREAM);

#define MYLOG_INFO(CHANNEL, STREAM)                                                                              \
  MYLOG((CHANNEL), log_info, STREAM);

#define MYLOG_WARN(CHANNEL, STREAM)                                                                              \
  MYLOG((CHANNEL), log_warn, STREAM);

#define MYLOG_ERROR(CHANNEL, STREAM)                                                                             \
  MYLOG((CHANNEL), log_error, STREAM);

#define MYLOG_FATAL(CHANNEL, STREAM)                                                                             \
  MYLOG((CHANNEL), log_critical, STREAM);

#define MYLOG_TRACE(CHANNEL)                                                                                     \
  MYLOG((CHANNEL), log_debug, BOOST_CURRENT_FUNCTION);

///
/// FMT based logging macros notice the F on the functions!
///
#define MYLOGF(CHANNEL, LEVEL, FMT_STR, ...)                                                                    \
  MYLOG_INTERNAL_FMT_STR(CHANNEL, LEVEL, FMT_STR, __VA_ARGS__)

#define MYLOG_DEBUGF(CHANNEL, FMT_STR, ...)                                                                      \
  MYLOGF((CHANNEL), log_debug, FMT_STR, __VA_ARGS__);

#define MYLOG_INFOF(CHANNEL, FMT_STR, ...)                                                                       \
  MYLOGF((CHANNEL), log_info, FMT_STR, __VA_ARGS__);

#define MYLOG_WARNF(CHANNEL, FMT_STR, ...)                                                                       \
  MYLOGF((CHANNEL), log_warn, FMT_STR, __VA_ARGS__);

#define MYLOG_ERRORF(CHANNEL, FMT_STR, ...)                                                                      \
  MYLOGF((CHANNEL), log_error, FMT_STR, __VA_ARGS__);

#define MYLOG_FATALF(CHANNEL, FMT_STR, ...)                                                                      \
  MYLOGF((CHANNEL), log_critical, FMT_STR, __VA_ARGS__);

#endif // MY_STD_UTIL_LOG_STUDIO_HPP