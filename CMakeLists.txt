cmake_minimum_required(VERSION 3.9)

# Setup flags
set(CFLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} -DDEV_BUILD")
set(CMAKE_CXX_FLAGS_PRODUCTION "${CMAKE_CXX_FLAGS_RELEASE} ${CFLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_PRODUCTION} -DDEV_BUILD ${CFLAGS}")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type was specified, default to Production")
    set(CMAKE_BUILD_TYPE "Production")
endif ()

# Setup configuration
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CONFIGURATION "Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CONFIGURATION "Release")
elseif(CMAKE_BUILD_TYPE MATCHES Production)
    set(CONFIGURATION "Production")
endif ()

# Simple notification
message(STATUS "Conure2D build started with ${CONFIGURATION} configuration")

# Conure2D using some features from C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 3)

project(Conure2D)

# Include directory in case of user have SMFL in Conure2D folder
include_directories(./Src)
include_directories(./)

# Static libs
add_subdirectory(Src/Utility)
add_subdirectory(Src/Input)
add_subdirectory(Src/Core)
add_subdirectory(Src/Render)
add_subdirectory(Src/Engine)