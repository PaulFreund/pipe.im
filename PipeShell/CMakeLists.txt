#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeShell)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

file(GLOB PIPE_SHELL_SRC "*.cpp")
add_executable(PipeShell ${PIPE_SHELL_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeShell pipe)

#-------------------------------------------------------------------------------
# POCO

find_path(POCO_INCLUDE NAMES Poco/Poco.h)

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

include_directories(POCO_INCLUDE)
target_link_libraries (PipeShell ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeShell
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)

#-------------------------------------------------------------------------------
