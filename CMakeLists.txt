cmake_minimum_required(VERSION 3.9)
include(ExternalProject)

#######################################################################################################################
# Setup stuff
## Flags
set(CFLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} -DDEV_BUILD")
set(CMAKE_CXX_FLAGS_PRODUCTION "${CMAKE_CXX_FLAGS_RELEASE} ${CFLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_RELEASE} -DDEV_BUILD ${CFLAGS}")

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
set(EXTERNAL_INSTALL_DIR ../External)

#-------------------------------------------------------------------------------------
## Date
## Note: It is a simple header-only library so we can just download it to use

### Get Date library
ExternalProject_Add(Date
                    PREFIX         ${EXTERNAL_INSTALL_DIR}
                    GIT_REPOSITORY https://github.com/HowardHinnant/date.git
                    GIT_TAG        v2.4.1
                    # Build step is not required, so turn off all commands
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND ""
                    INSTALL_COMMAND "")
### Include Date dependencies
include_directories(./External/src/Date/include)

#-------------------------------------------------------------------------------------
## SFML
### Get SFML library
ExternalProject_Add(SFML
                    GIT_REPOSITORY https://github.com/SFML/SFML
                    PREFIX ${EXTERNAL_INSTALL_DIR}
                    GIT_TAG        2.5.1
                    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
                    # Install step is not required, so turn it off
                    INSTALL_COMMAND "")
### Include SFML dependencies
include_directories(./External/src/SFML/include)
### SFML libs
set(SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/src/SFML-build/lib")
#### SFML-System
add_library(SFML-System STATIC IMPORTED)
set_target_properties(SFML-System PROPERTIES
                      IMPORTED_LOCATION "${SFML_LIB_PATH}/libsfml-system-s.a")
#### SFML-Window
add_library(SFML-Window STATIC IMPORTED)
set_target_properties(SFML-Window PROPERTIES
                      IMPORTED_LOCATION "${SFML_LIB_PATH}/libsfml-window-s.a")
#### SFML-Graphics
add_library(SFML-Graphics STATIC IMPORTED)
set_target_properties(SFML-Graphics PROPERTIES
                      IMPORTED_LOCATION "${SFML_LIB_PATH}/libsfml-graphics-s.a")

#-------------------------------------------------------------------------------------
## Google Test
### Get gtest library
ExternalProject_Add(GoogleTest
                    GIT_REPOSITORY https://github.com/google/googletest
                    PREFIX ${EXTERNAL_INSTALL_DIR}
                    GIT_TAG        release-1.8.1
                    # Install step is not required, so turn it off
                    INSTALL_COMMAND "")
### Include gtest dependencies
include_directories(./External/src/GoogleTest/googletest/include)
### Gtest libs
set(GTEST_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/src/GoogleTest-build/googlemock")
#### G-Test
add_library(G-Test STATIC IMPORTED)
set_target_properties(G-Test PROPERTIES
                      IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest.a")
#### G-Test_main
add_library(G-Test_main STATIC IMPORTED)
set_target_properties(G-Test_main PROPERTIES
                      IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest_main.a")

#######################################################################################################################
# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

#######################################################################################################################
# Project settings
project(Conure2D)

## Setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

## Include directories
include_directories(./Src)

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