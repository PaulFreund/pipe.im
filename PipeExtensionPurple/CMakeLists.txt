cmake_minimum_required(VERSION 2.8)
project(PipeExtensionPurple)

include_directories(..)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

set (PIPE_EXTENSION_PURPLE_MAIN PipeExtensionPurpleAPI.cpp)

add_library(PipeExtensionPurple SHARED ${PIPE_EXTENSION_PURPLE_MAIN})

