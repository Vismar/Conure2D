cmake_minimum_required(VERSION 3.9)
project(Render)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

add_library(Render
            Components/SpriteRenderComponent.cpp
            Components/SpriteRenderComponent.hpp
            Window/Window.cpp
            Window/Window.hpp
            Window/WindowSettings.cpp
            Window/WindowSettings.hpp
            RenderSystem.cpp
            RenderSystem.hpp
            RenderSystemInterface.hpp)

# Dependencies
add_dependencies(Render SFML)

# Prefix
set_target_properties(Render PROPERTIES PREFIX "")
# Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Render PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Render PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)