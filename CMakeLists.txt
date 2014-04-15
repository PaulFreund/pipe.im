#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(pipe.im)

#-------------------------------------------------------------------------------
# Project settings

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#-------------------------------------------------------------------------------
# Project components

add_subdirectory(libpipe)
add_subdirectory(PipeExtensionPurple)
add_subdirectory(PipeShell)
add_subdirectory(PipeWebsocketShell)

#-------------------------------------------------------------------------------
