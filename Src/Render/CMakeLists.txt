cmake_minimum_required(VERSION 3.9)
project(Render)

set(Src ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

include_directories(${Src}/)

add_library(Render
            ${Src}/Render/Components/SpriteRenderComponent.cpp
            ${Src}/Render/Components/SpriteRenderComponent.hpp
            ${Src}/Render/Window/Window.cpp
            ${Src}/Render/Window/Window.hpp
            ${Src}/Render/Window/WindowSettings.cpp
            ${Src}/Render/Window/WindowSettings.hpp
            ${Src}/Render/RenderSystem.cpp
            ${Src}/Render/RenderSystem.hpp
            ${Src}/Render/RenderSystemInterface.hpp)

# Prefix
set_target_properties(Render PROPERTIES PREFIX "")
# Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Render PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Render PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)