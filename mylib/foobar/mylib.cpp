///
/// This is the internal log header for STUDIO
/// DO NOT INCLUDE use log.hpp

/// Copyright (C) Nanosurf AG - All Rights Reserved (2017)
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential
/// https://www.nanosurf.com
///

#include <foobar/mylib.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>


#include <spdlog/sinks/msvc_sink.h>

#include <vector>
#include <array>
#include <queue>
#include <ctime>
#include <iomanip>
#include <map>

namespace foobar
{
namespace detail
{

///
///
///
std::atomic_bool log_is_setup{ false };
uint64_t log_user_marker_counter = 0;
///
///
///
struct log_buffer_enrty
{
  log_level level_;
  log_channel_type log_channel_;
  log_message_type log_message_;
};
std::vector<log_buffer_enrty> log_buffer;

///
///
///
auto spdlog_level(log_level level) -> spdlog::level::level_enum
{
  switch(level)
  {
    case log_level::log_trace   : return spdlog::level::level_enum::trace;
    case log_level::log_debug   : return spdlog::level::level_enum::debug;
    case log_level::log_info    : return spdlog::level::level_enum::info;
    case log_level::log_warn    : return spdlog::level::level_enum::warn;
    case log_level::log_error   : return spdlog::level::level_enum::err;
    case log_level::log_critical: return spdlog::level::level_enum::critical;
    case log_level::log_off     : return spdlog::level::level_enum::off;
  }
  return spdlog::level::level_enum::critical;
}

///
///
///
auto level_to_string(log_level level) -> std::string
{
  const auto l = spdlog_level(level);
  const auto strv = spdlog::level::to_string_view(l);
  return std::string{ strv.data(), strv.size() };
}

///
///
///
auto create_filename_from_pattern(const std::string& pattern) -> std::string
{
  const auto pattern_time = spdlog::pattern_time_type::local;
  const auto end_of_line = std::string{""};

  spdlog::pattern_formatter pattern_formatter(pattern, pattern_time, end_of_line);
  spdlog::details::log_msg dummy_msg("channel", spdlog::level::trace, "msg");
  spdlog::memory_buf_t buffer;
  pattern_formatter.format(dummy_msg, buffer);

  std::string file_name(buffer.begin(), buffer.end());
  return file_name;
}

///
///
///
struct logger_container
{
  ///
  ///
  using optional_logger_type = std::shared_ptr<spdlog::logger>;

  ///
  ///
  static constexpr size_t max_number_loggers = 100;

  ///
  ///
  ///
  ~logger_container()
  {
    detail::log_is_setup = false;
    spdlog::shutdown();
  }

  ///
  ///
  ///
  auto logger(const std::string& channel) -> optional_logger_type&
  {
    const auto itr = std::find(std::begin(index_map), std::end(index_map), channel);

    if(itr != std::end(index_map))
    {
      const auto idx = std::distance(std::begin(index_map), itr);
      return loggers[idx];
    }

    auto new_logger = std::make_shared<spdlog::async_logger>(channel, std::begin(sinks), std::end(sinks), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    new_logger->set_level(level_for_channel(channel));
    new_logger->set_pattern(default_pattern);

    index_map[next_index] = channel;
    loggers[next_index] = new_logger;
    ++next_index;

    return loggers[next_index-1];
  }

  ///
  ///
  ///
  auto level_for_channel(const std::string& channel) const -> spdlog::level::level_enum
  {
    for (decltype(auto) channel_level_pair : channel_log_level)
    {
      if (channel_level_pair.first == channel)
      {
        return channel_level_pair.second;
      }
    }
    return default_level;
  }

  std::array<std::string, max_number_loggers> index_map;
  std::array<optional_logger_type, max_number_loggers> loggers;
  std::string default_pattern;
  std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;
  std::chrono::milliseconds flush_interval;
  size_t next_index{0};
  spdlog::level::level_enum default_level;
  std::vector<std::pair<std::string, spdlog::level::level_enum>> channel_log_level;
};

///
///
///
auto get_loggers(bool reset = false) -> logger_container&
{
  static logger_container loggers{};
  if(reset)
  {
    loggers = logger_container{};
  }
  return loggers;
}

///
///
///
auto get_logger(const std::string& channel) -> spdlog::logger&
{
  decltype(auto) loggers = get_loggers();
  return *(loggers.logger(channel));
}

} //namespace

///
///
auto log_setup(const log_configuration& /*config*/) -> void
{
  detail::log_is_setup = false;
  spdlog::drop_all();
  auto& loggers = detail::get_loggers(true);

  spdlog::init_thread_pool(128, 1);

  std::shared_ptr<spdlog::sinks::sink> new_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  new_sink->set_level(spdlog::level::trace);
  loggers.sinks.push_back(new_sink);

  detail::log_is_setup = true;

  for(decltype(auto) msg : detail::log_buffer)
  {
    log(msg.level_, msg.log_channel_, msg.log_message_);
  }
  detail::log_buffer.clear();
}

///
///
auto log(log_level level, log_channel_type channel, const log_message_type& msg) -> void
{
  if(!detail::log_is_setup)
  {
    detail::log_buffer.push_back(detail::log_buffer_enrty{ level, channel, msg });
  }
  else
  {
    decltype (auto)  logger = detail::get_logger(channel);
    logger.log(detail::spdlog_level(level), msg);
    logger.flush();
  }
}

///
///
auto log_user_marker() -> void
{
  ++detail::log_user_marker_counter;
  log(log_level::log_info, "UserMarker", fmt::format("---------- Marker {} ---------- ", detail::log_user_marker_counter));
}

///
///
auto log_level_to_string(log_level level)->std::string
{
  return detail::level_to_string(level);
}

} //namespace foobar

