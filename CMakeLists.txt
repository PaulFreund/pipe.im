#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(pipe.im)

#-------------------------------------------------------------------------------
# Project components

add_subdirectory(libpipe)
add_subdirectory(PipeExtensionPurple)
add_subdirectory(PipeTerminal)
add_subdirectory(PipeWebsocketTerminal)

#-------------------------------------------------------------------------------
