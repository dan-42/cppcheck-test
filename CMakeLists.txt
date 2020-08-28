cmake_minimum_required(VERSION 3.17)

project(test-cppcheck)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs_external)
add_subdirectory(mylib)
add_subdirectory(myapp)