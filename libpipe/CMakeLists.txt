#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(libpipe)

#-------------------------------------------------------------------------------
# Project configuration

if(DARWIN)
	set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
else()
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB LIB_PIPE_SRC "*.cpp" "*.c")

add_library(pipe SHARED ${LIB_PIPE_SRC})

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_FOUNDATION NAMES PocoFoundation)

set(POCO_LIBRARIES
        ${POCO_FOUNDATION}
)

target_link_libraries (pipe ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS pipe
        LIBRARY DESTINATION lib
)

#-------------------------------------------------------------------------------
