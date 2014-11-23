#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(libpipe)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB LIB_PIPE_SRC "*.cpp" "*.c")

add_library(pipe SHARED ${LIB_PIPE_SRC})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS pipe
        LIBRARY DESTINATION lib
)

#-------------------------------------------------------------------------------
