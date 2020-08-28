cmake_minimum_required(VERSION 3.17)

project(mylib)

##
## Include subdirectories
##
file(GLOB_RECURSE MYLIB_SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/foobar/*.cpp")

##
## Create target
##
add_library(mylib STATIC ${MYLIB_SRC_FILES})

##
## Add target include dirs and target sources
##
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

###
### Link against external dependencies
###
target_link_libraries(mylib PUBLIC libs_external::all)