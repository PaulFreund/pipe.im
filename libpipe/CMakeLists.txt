cmake_minimum_required(VERSION 2.8)
project(libpipe)

include_directories(${CMAKE_SOURCE_DIR}/ChaiScript/include)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

set (LIBPIPE_MAIN LibPipeAPI.cpp)

add_library(pipe SHARED ${LIBPIPE_MAIN})

