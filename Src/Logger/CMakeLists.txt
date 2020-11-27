cmake_minimum_required(VERSION 3.9)
project(Logger)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build static library
add_library(Logger STATIC
        Logger.hpp
        Logger.cpp)

## Prefix
set_target_properties(Logger PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Logger PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Logger PROPERTIES RELEASE_POSTFIX "-r")
endif ()

########################################################################################################################