cmake_minimum_required(VERSION 3.17)

project(myapp)

file(GLOB_RECURSE myapp_CPP_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_executable(myapp)

target_include_directories(myapp PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_sources(myapp PRIVATE ${myapp_CPP_FILES})
target_link_libraries(myapp PRIVATE mylib)