#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeWebsocketShell)

#-------------------------------------------------------------------------------
# Project configuration

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

file(GLOB PIPE_WEBSOCKET_SHELL_SRC "*.cpp")
add_executable(PipeWebsocketShell ${PIPE_WEBSOCKET_SHELL_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(PipeWebsocketShell pipe)

#-------------------------------------------------------------------------------
# POCO

find_library(POCO_FOUNDATION NAMES PocoFoundation)
find_library(POCO_DATA NAMES PocoData)
find_library(POCO_UTIL NAMES PocoUtil)
find_library(POCO_NET NAMES PocoNet)
find_library(POCO_MYSQL NAMES PocoMySQL PocoDataMySQL)
find_library(POCO_SQLITE NAMES PocoSQLite PocoDataSQLite)

set(POCO_LIBRARIES 
	${POCO_FOUNDATION}
	${POCO_DATA} 
	${POCO_UTIL} 
	${POCO_NET} 
	${POCO_SQLITE}
	${POCO_MYSQL}
)

target_link_libraries (PipeWebsocketShell ${POCO_LIBRARIES})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeWebsocketShell
        RUNTIME DESTINATION bin
)

install(DIRECTORY static/ DESTINATION share/pipe/WebsocketShell/static)

#-------------------------------------------------------------------------------
