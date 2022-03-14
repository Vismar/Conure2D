cmake_minimum_required(VERSION 3.9)
project(Render)

#######################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../../Lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../../../Lib")

#######################################################################################################################
# Build static library
add_library(Render
            Components/SpriteRenderComponent.hpp
            Components/SpriteRenderComponent.cpp
            Window/Window.hpp
            Window/Window.cpp
            Window/WindowSettings.hpp
            Window/WindowSettings.cpp
            RenderSystem.hpp
            RenderSystem.cpp
            RenderSystemInterface.hpp)

## Dependencies
add_dependencies(Render SFML)

## Prefix
set_target_properties(Render PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Render PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Render PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################