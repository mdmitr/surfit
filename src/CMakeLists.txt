cmake_minimum_required(VERSION 2.8)

include(CheckIncludeFile)

project(surfit)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Widgets finds its own dependencies.
find_package(TCL REQUIRED)

find_package(ZLIB)

# ----------------------------------
# projects
# ----------------------------------

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	set(PLATFORM "x64")
else()
	set(PLATFORM "Win32")
endif()


#config
set(VERSION "3.1")
CHECK_INCLUDE_FILE(string.h  HAVE_STRING_H)
CHECK_INCLUDE_FILE(stdlib.h  HAVE_STDLIB_H)
CHECK_INCLUDE_FILE(unistd.h  HAVE_UNISTD_H)

configure_file(config.h.in config.h)


# Libraries
add_subdirectory(sstuff)
add_subdirectory(surfit)
add_subdirectory(surfit_io)

if (ZLIB_FOUND)
	add_subdirectory(globe)
endif(ZLIB_FOUND)

add_subdirectory(freeflow)

# Executabels
add_subdirectory(surfit_cmd)


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

