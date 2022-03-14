cmake_minimum_required(VERSION 3.9)
project(Render)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build static library
add_library(Render STATIC
            RenderSystem.hpp
            RenderSystem.cpp TriangleRenderer.cpp TriangleRenderer.hpp)

## Dependencies
add_dependencies(Render Utility Logger Tracer VkWrapper GLFWWrapper GLM)
target_link_libraries(Render Utility Logger Tracer VkWrapper GLFWWrapper)

## Prefix
set_target_properties(Render PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Render PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Render PROPERTIES RELEASE_POSTFIX "-r")
endif ()

########################################################################################################################