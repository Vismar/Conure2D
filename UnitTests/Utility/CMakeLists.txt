cmake_minimum_required(VERSION 3.9)
project(UtilityTest)

#######################################################################################################################
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Test/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Test/")

#######################################################################################################################
# Build executable
add_executable(UtilityTest
               Containers/LockFreeLinkedQueueTests.cpp
               Containers/RingBufferTest.cpp)

## Link libraries
target_link_libraries(UtilityTest gtest gtest_main pthread)
target_link_libraries(UtilityTest Utility)

## Prefix
set_target_properties(UtilityTest PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(UtilityTest PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(UtilityTest PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################
# Tests
add_test(NAME TestUtility COMMAND UtilityTest)

#######################################################################################################################