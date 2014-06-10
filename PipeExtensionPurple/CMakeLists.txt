#-------------------------------------------------------------------------------
# Project definition

cmake_minimum_required(VERSION 2.8)
project(PipeExtensionPurple)

#-------------------------------------------------------------------------------
# Project configuration

if(DARWIN)
        set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
else()
        set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

file(GLOB PIPE_EXTENSION_PURPLE_SRC "*.cpp")
add_library(PipeExtensionPurple SHARED ${PIPE_EXTENSION_PURPLE_SRC})

#-------------------------------------------------------------------------------
# General dependencies

include_directories(${CMAKE_SOURCE_DIR})

#-------------------------------------------------------------------------------
# Glib-2

find_package(PkgConfig REQUIRED)
pkg_check_modules(PKG_GLIB REQUIRED glib-2.0)
find_path(GLIB2_MAIN_INCLUDE_DIR glib.h PATH_SUFFIXES glib-2.0 PATHS ${PKG_GLIB_INCLUDE_DIRS})
find_library(GLIB2_LIBRARIES NAMES glib-2.0 PATHS ${PKG_GLIB_LIBRARY_DIRS})
find_library(GLIB2_THREAD NAMES gthread-2.0 PATHS ${PKG_GLIB_LIBRARY_DIRS})
find_path(GLIB2_INTERNAL_INCLUDE_DIR glibconfig.h PATH_SUFFIXES glib-2.0/include PATHS ${PKG_GLIB_INCLUDE_DIRS} ${PKG_GLIB_LIBRARIES} ${CMAKE_SYSTEM_LIBRARY_PATH})
set(GLIB2_LIBRARIES ${GLIB2_LIBRARIES} ${GLIB2_THREAD})
set(GLIB2_INCLUDE_DIR ${GLIB2_MAIN_INCLUDE_DIR} ${GLIB2_INTERNAL_INCLUDE_DIR})

include_directories(${GLIB2_INCLUDE_DIR})
target_link_libraries(PipeExtensionPurple ${GLIB2_LIBRARIES})


#-------------------------------------------------------------------------------
# Purple

find_library(PURPLE_LIBRARY NAMES purple)
find_path(PURPLE_INCLUDE_DIR NAMES "purple.h" PATH_SUFFIXES libpurple )

include_directories(${PURPLE_INCLUDE_DIR})
target_link_libraries(PipeExtensionPurple ${PURPLE_LIBRARY})

#-------------------------------------------------------------------------------
# Installation

install(TARGETS PipeExtensionPurple
        LIBRARY DESTINATION lib/pipe/
)

#-------------------------------------------------------------------------------
