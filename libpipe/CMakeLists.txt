#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(libpipe)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

file(GLOB LIB_PIPE_SRC "*.cpp")
add_library(pipe SHARED ${LIB_PIPE_SRC})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS pipe
        LIBRARY DESTINATION lib
)

#-------------------------------------------------------------------------------
