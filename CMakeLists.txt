cmake_minimum_required(VERSION 3.9)
include(ExternalProject)

########################################################################################################################
# Setup stuff
## Flags

set(CFLAGS "-m64 -Wall")
set(GCC_COMPILATION_FLAGS "-static -fcoroutines")
set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} -DDEV_BUILD ${GCC_COMPILATION_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_RELEASE} ${CFLAGS} ${GCC_COMPILATION_FLAGS}")

## Default build type
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type was specified, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

set(OUTPUT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/Output)

## Configuration
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CONFIGURATION "Debug")
    set(OUTPUT_BIN ${OUTPUT_FOLDER}/Bin/Debug CACHE INTERNAL "")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CONFIGURATION "Release")
    set(OUTPUT_BIN ${OUTPUT_FOLDER}/Bin/Release CACHE INTERNAL "")
endif ()

set(OUTPUT_LIB ${OUTPUT_FOLDER}/Lib CACHE INTERNAL "")

## Simple notification of chosen configuration
message(STATUS "Conure2D build started with ${CONFIGURATION} configuration")

########################################################################################################################
# Install dependencies
set(EXTERNAL_INSTALL_DIR ../External)

#-----------------------------------------------------------------------------------------------------------------------
## Date
## Note: It is a simple header-only library so just download it

### Get Date library
ExternalProject_Add(Date
                    SOURCE_DIR        "${EXTERNAL_INSTALL_DIR}/Date/src"
                    BINARY_DIR        "${EXTERNAL_INSTALL_DIR}/Date/build"
                    STAMP_DIR         "${EXTERNAL_INSTALL_DIR}/Date/stamp"
                    TMP_DIR           "${EXTERNAL_INSTALL_DIR}/Date/tmp"
                    GIT_REPOSITORY    https://github.com/HowardHinnant/date
                    GIT_TAG           v2.4.1
                    # Build step is not required, so turn off all commands
                    UPDATE_COMMAND    ""
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND     ""
                    INSTALL_COMMAND   "")
### Include Date dependencies
include_directories(./External/Date/src/include)

#-----------------------------------------------------------------------------------------------------------------------
## GLM
## Note: It is a simple header-only library so just download it

### Get GLM library
ExternalProject_add(GLM
                    SOURCE_DIR        "${EXTERNAL_INSTALL_DIR}/GLM/src"
                    BINARY_DIR        "${EXTERNAL_INSTALL_DIR}/GLM/build"
                    STAMP_DIR         "${EXTERNAL_INSTALL_DIR}/GLM/stamp"
                    TMP_DIR           "${EXTERNAL_INSTALL_DIR}/GLM/tmp"
                    GIT_REPOSITORY    https://github.com/g-truc/glm
                    GIT_TAG           0.9.9.8
                    # Build step is not required, so turn off all commands
                    UPDATE_COMMAND    ""
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND     ""
                    INSTALL_COMMAND   "")
### Include GLM dependencies
include_directories(./External/GLM/src)

#-----------------------------------------------------------------------------------------------------------------------
## GLFW
### Get glfw library
ExternalProject_Add(GLFW
                    GIT_REPOSITORY  https://github.com/glfw/glfw
                    SOURCE_DIR      "${EXTERNAL_INSTALL_DIR}/GLFW/src"
                    BINARY_DIR      "${EXTERNAL_INSTALL_DIR}/GLFW/build"
                    STAMP_DIR       "${EXTERNAL_INSTALL_DIR}/GLFW/stamp"
                    TMP_DIR         "${EXTERNAL_INSTALL_DIR}/GLFW/tmp"
                    GIT_TAG         3.3.2
                    # Install step is not required, so turn it off
                    UPDATE_COMMAND  ""
                    INSTALL_COMMAND "")
### Include GLFW dependencies
include_directories(./External/GLFW/src/include)
### GLFW lib
set(GLFW_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/GLFW/build/src/libglfw3.a")
add_library(GLFW-Lib STATIC IMPORTED)
set_target_properties(GLFW-Lib PROPERTIES
                      IMPORTED_LOCATION "${GLFW_LIB_PATH}"
                      GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE
                      GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE
                      GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#-----------------------------------------------------------------------------------------------------------------------
## Vulkan
### Set variables for search
if (NOT CMAKE_FIND_LIBRARY_PREFIXES)
    message("CMAKE_FIND_LIBRARY_PREFIXES was not set, setting it to default value...")
    set(CMAKE_FIND_LIBRARY_PREFIXES "")
endif()
if (NOT CMAKE_FIND_LIBRARY_SUFFIXES)
    message("CMAKE_FIND_LIBRARY_SUFFIXES was not set, setting it to default value...")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
endif()

### Try to find Vulkan via find_package
unset(Vulkan_LIBRARY CACHE)
find_package(Vulkan)

### If Vulkan was not found then try to find it via env variables
if (NOT Vulkan_FOUND)
    message("Vulkan lib was not found, searching for env variables...")
    if (DEFINED ENV{VK_SDK_PATH})
        message("Found env variable for Vulkan SDK: $ENV{VK_SDK_PATH}")
        find_library(Vulkan_LIBRARY NAMES vulkan-1 libvulkan PATHS "$ENV{VK_SDK_PATH}/lib" REQUIRED)
        if (NOT DEFINED Vulkan_INCLUDE_DIR)
            message("Vulkan include path was not found, using found env variable...")
            set(Vulkan_INCLUDE_DIR "$ENV{VK_SDK_PATH}/Include")
        endif()
        set(Vulkan_FOUND ON)
        message("Vulkan lib -> ${Vulkan_LIBRARY}")
        message("Vulkan inc -> ${Vulkan_INCLUDE_DIR}")
    else(DEFINED ENV{VULKAN_SDK})
        message("Found env variable for Vulkan SDK: $ENV{VULKAN_SDK}")
        find_library(Vulkan_LIBRARY NAMES vulkan-1 libvulkan PATHS "$ENV{VK_SDK_PATH}/lib" REQUIRED)
        if (NOT DEFINED Vulkan_INCLUDE_DIR)
            message("Vulkan include path was not found, using found env variable...")
            set(Vulkan_INCLUDE_DIR "$ENV{VK_SDK_PATH}/Include")
        endif()
        set(Vulkan_FOUND ON)
        message("Vulkan lib -> ${Vulkan_LIBRARY}")
        message("Vulkan inc -> ${Vulkan_INCLUDE_DIR}")
    endif()
endif()

### Include Vulkan dependencies
if (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan was not found")
else()
    include_directories(${Vulkan_INCLUDE_DIR})
endif()

#-----------------------------------------------------------------------------------------------------------------------
## Google Test
### Get gtest library
ExternalProject_Add(GoogleTest
                    GIT_REPOSITORY  https://github.com/google/googletest
                    SOURCE_DIR      "${EXTERNAL_INSTALL_DIR}/GoogleTest/src"
                    BINARY_DIR      "${EXTERNAL_INSTALL_DIR}/GoogleTest/build"
                    STAMP_DIR       "${EXTERNAL_INSTALL_DIR}/GoogleTest/stamp"
                    TMP_DIR         "${EXTERNAL_INSTALL_DIR}/GoogleTest/tmp"
                    GIT_TAG         release-1.8.1
                    # Install step is not required, so turn it off
                    UPDATE_COMMAND  ""
                    INSTALL_COMMAND "")
### Include gtest dependencies
include_directories(./External/GoogleTest/src/googletest/include)
### Gtest libs
set(GTEST_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/GoogleTest/build/googlemock")
#### G-Test
add_library(G-Test STATIC IMPORTED)
set_target_properties(G-Test PROPERTIES
                      IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest.a")
#### G-Test_main
add_library(G-Test_main STATIC IMPORTED)
set_target_properties(G-Test_main PROPERTIES
                      IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest_main.a")


########################################################################################################################
# C++20 is required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

########################################################################################################################
# Project settings
project(Conure2D)

## Setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

## Include directories
include_directories(./Src)

#link_libraries(${Vulkan_LIBRARY})

## Static libs
add_subdirectory(Src/Utility)
add_subdirectory(Src/Logger)
add_subdirectory(Src/Tracer)
add_subdirectory(Src/GLFWWrapper)
add_subdirectory(Src/VkWrapper)

add_subdirectory(Src/TestApp)

#add_subdirectory(Src/Input)
#add_subdirectory(Src/Core)
#add_subdirectory(Src/Render)
#add_subdirectory(Src/Engine)


#######################################################################################################################
# Tests
enable_testing ()
add_subdirectory(UnitTests/Utility)
#######################################################################################################################