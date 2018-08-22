cmake_minimum_required(VERSION 3.9)
project(Engine)

#######################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

#######################################################################################################################
# Build static library
add_library(Engine
            Main/EngineApp.cpp
            Main/EngineApp.hpp
            EngineInterface.cpp
            EngineInterface.hpp
            EngineInterfaceDefinitions.inl)

## Dependencies
add_dependencies(Engine SFML)

## Prefix
set_target_properties(Engine PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Engine PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Engine PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################