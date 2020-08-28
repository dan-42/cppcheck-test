cmake_minimum_required(VERSION 3.17)

project(fmt)

add_library(fmt INTERFACE IMPORTED GLOBAL)

target_include_directories(fmt SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(
  fmt
  INTERFACE
    FMT_HEADER_ONLY=1
)

add_library(fmt::fmt ALIAS fmt)