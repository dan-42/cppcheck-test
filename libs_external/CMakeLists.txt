cmake_minimum_required(VERSION 3.17)

project(libs_external)

add_subdirectory(boost)
add_subdirectory(fmt)
add_subdirectory(spdlog)

##
## All header only libs
##
add_library(libs_external_header_only INTERFACE IMPORTED GLOBAL)
target_link_libraries(libs_external_header_only
  INTERFACE
    Boost::boost
    fmt::fmt
    spdlog::spdlog
)
add_library(libs_external::header_only ALIAS libs_external_header_only)


##
## All external libs combined as one target
##
add_library(libs_external_all INTERFACE IMPORTED GLOBAL)
target_link_libraries(libs_external_all
  INTERFACE
    libs_external::header_only
)

add_library(libs_external::all ALIAS libs_external_all)
