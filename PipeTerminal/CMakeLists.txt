#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeTerminal)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB PIPE_TERMINAL_SRC "*.cpp")
add_executable(PipeTerminal ${PIPE_TERMINAL_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeTerminal pipe)

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_UTIL NAMES PocoUtil)

set(POCO_LIBRARIES 
	${POCO_UTIL} 
)

target_link_libraries (PipeTerminal ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeTerminal
        RUNTIME DESTINATION bin
)

#-------------------------------------------------------------------------------
