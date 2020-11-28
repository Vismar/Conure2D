cmake_minimum_required(VERSION 3.9)
project(Tracer)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build static library
add_library(Tracer STATIC
        TraceScopeTimer.hpp
        TraceScopeTimer.cpp)

## Dependencies
add_dependencies(Tracer Utility Logger)
target_link_libraries(Tracer Utility Logger)

## Prefix
set_target_properties(Tracer PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Tracer)
    set_target_properties(Tracer PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Tracer PROPERTIES RELEASE_POSTFIX "-r")
endif ()

########################################################################################################################