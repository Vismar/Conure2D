cmake_minimum_required(VERSION 3.9)
project(GLFWWrapper)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Builds static library
add_library(GLFWWrapper STATIC
        Context.hpp
        Context.cpp
        VideoMode.hpp
        VideoMode.cpp
        Monitor.hpp
        Monitor.cpp
        Window.hpp
        Window.cpp)

## Dependencies
add_dependencies(GLFWWrapper Utility Logger GLFW-Lib)
target_link_libraries(GLFWWrapper Utility Logger GLFW-Lib)

## Prefix
set_target_properties(GLFWWrapper PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(GLFWWrapper PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(GLFWWrapper PROPERTIES RELEASE_POSTFIX "-r")
endif ()

########################################################################################################################