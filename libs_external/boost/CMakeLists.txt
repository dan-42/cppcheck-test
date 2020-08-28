cmake_minimum_required(VERSION 3.17)

project(Boost)

add_library(Boost INTERFACE IMPORTED GLOBAL)

target_include_directories(Boost SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(Boost INTERFACE
  -DBOOST_ALL_NO_LIB
  -DBOOST_ERROR_CODE_HEADER_ONLY
)

add_library(Boost::boost ALIAS Boost)