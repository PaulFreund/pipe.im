#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeExtensionPurple)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

file(GLOB PIPE_EXTENSION_PURPLE_SRC "*.cpp")
add_library(PipeExtensionPurple SHARED ${PIPE_EXTENSION_PURPLE_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeExtensionPurple
        LIBRARY DESTINATION lib/pipe/
)

#-------------------------------------------------------------------------------
