cmake_minimum_required(VERSION 3.17)

project(spdlog)

add_library(spdlog INTERFACE IMPORTED GLOBAL)

target_include_directories(spdlog SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)


add_library(spdlog::spdlog ALIAS spdlog)