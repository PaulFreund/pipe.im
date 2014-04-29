#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeTerminal)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

file(GLOB PIPE_TERMINAL_SRC "*.cpp")
add_executable(PipeTerminal ${PIPE_TERMINAL_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeTerminal pipe)

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_FOUNDATION NAMES PocoFoundation)
find_library(POCO_DATA NAMES PocoData)
find_library(POCO_UTIL NAMES PocoUtil)
find_library(POCO_MYSQL NAMES PocoMySQL PocoDataMySQL)
find_library(POCO_SQLITE NAMES PocoSQLite PocoDataSQLite)

set(POCO_LIBRARIES 
	${POCO_FOUNDATION}
	${POCO_DATA} 
	${POCO_UTIL} 
	${POCO_SQLITE}
	${POCO_MYSQL}
)

target_link_libraries (PipeTerminal ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeTerminal
        RUNTIME DESTINATION bin
)

#-------------------------------------------------------------------------------
