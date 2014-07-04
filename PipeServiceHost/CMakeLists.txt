#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeServiceHost)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB PIPE_SERVICE_HOST_SRC "*.cpp")
add_executable(PipeServiceHost ${PIPE_SERVICE_HOST_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeServiceHost pipe)

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_UTIL NAMES PocoUtil)
find_library(POCO_NET NAMES PocoNet)

set(POCO_LIBRARIES 
	${POCO_UTIL} 
	${POCO_NET} 
)

target_link_libraries (PipeServiceHost ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeServiceHost
        RUNTIME DESTINATION bin
)

install(DIRECTORY static/ DESTINATION share/pipe/PipeServiceHost/static)

#-------------------------------------------------------------------------------
