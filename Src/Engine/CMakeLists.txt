cmake_minimum_required(VERSION 3.10)
project(Engine)

set(Src ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

include_directories(${Src}/)

add_library(Engine
            ${Src}/Engine/Main/EngineApp.cpp
            ${Src}/Engine/Main/EngineApp.hpp
            ${Src}/Engine/EngineInterface.cpp
            ${Src}/Engine/EngineInterface.hpp
            ${Src}/Engine/EngineInterfaceDefinitions.inl)

# Prefix
set_target_properties(Engine PROPERTIES PREFIX "")
# Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Engine PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Engine PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)