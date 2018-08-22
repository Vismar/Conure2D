cmake_minimum_required(VERSION 3.9)
include(ExternalProject)

#######################################################################################################################
# Setup stuff
## Flags
set(CFLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} -DDEV_BUILD")
set(CMAKE_CXX_FLAGS_PRODUCTION "${CMAKE_CXX_FLAGS_RELEASE} ${CFLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_PRODUCTION} -DDEV_BUILD ${CFLAGS}")

## Default build type
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type was specified, default to Production")
    set(CMAKE_BUILD_TYPE "Production")
endif ()

## Configuration
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CONFIGURATION "Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CONFIGURATION "Release")
elseif(CMAKE_BUILD_TYPE MATCHES Production)
    set(CONFIGURATION "Production")
endif ()

## Simple notification of chosen configuration
message(STATUS "Conure2D build started with ${CONFIGURATION} configuration")

#######################################################################################################################
# Install dependencies
set(EXTERNAL_INSTALL_DIR ../External/)

## SFML
ExternalProject_Add(SFML
                    GIT_REPOSITORY https://github.com/SFML/SFML
                    PREFIX ${EXTERNAL_INSTALL_DIR})

## Google Test
ExternalProject_Add(GoogleTest
                    GIT_REPOSITORY https://github.com/google/googletest
                    PREFIX ${EXTERNAL_INSTALL_DIR})

## C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

#######################################################################################################################
# Project settings
project(Conure2D)

## Setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 3)

## Include directories
include_directories(./External/src/GoogleTest/googletest/include)
include_directories(./External/src/SFML/include)
include_directories(./Src)
include_directories(./)

## Static libs
add_subdirectory(Src/Utility)
add_subdirectory(Src/Input)
add_subdirectory(Src/Core)
add_subdirectory(Src/Render)
add_subdirectory(Src/Engine)

#######################################################################################################################
# Tests
enable_testing ()
add_subdirectory(UnitTests/Utility)
#######################################################################################################################