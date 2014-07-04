#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeServiceInstance)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB PIPE_SERVICE_INSTANCE_SRC "*.cpp")
add_executable(PipeServiceInstance ${PIPE_SERVICE_INSTANCE_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeServiceInstance pipe)

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_UTIL NAMES PocoUtil)
find_library(POCO_NET NAMES PocoNet)

set(POCO_LIBRARIES 
	${POCO_UTIL} 
	${POCO_NET} 
)

target_link_libraries (PipeServiceInstance ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeServiceInstance
        RUNTIME DESTINATION bin
)

#-------------------------------------------------------------------------------
