cmake_minimum_required(VERSION 3.9)
project(Utility)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build static library
add_library(Utility STATIC
            Assert.hpp
            Assert.cpp
            Time/Time.hpp
            Time/Time.cpp
            #Containers/AnyCallable/AnyCallable.hpp
            #Containers/AnyCallable/AnyCallable.inl
            #Containers/AnyCallable/AnyCallableHandler.cpp
            #Containers/AnyCallable/AnyCallableHandler.hpp
            #Containers/AnyCallable/BadAnyCallableCall.cpp
            #Containers/AnyCallable/BadAnyCallableCall.inl
            #Containers/AnyCallable/BadAnyCallableCall.hpp
            #Containers/LockedQueue/LockedQueue.hpp
            #Containers/LockedQueue/LockedQueue.inl
            Containers/RingBuffer/RingBuffer.hpp
            Containers/RingBuffer/RingBuffer.inl
            Containers/RingBuffer/RingBufferIterator.inl
            Containers/RingBuffer/RingBufferReverseIterator.inl
            #Helpers/EnumHelpers.hpp
            #Helpers/TypeHelpers.hpp
            #Helpers/VariantHelpers.hpp
            #Math/Vector2.hpp
            #Math/Vector2.inl
            #Math/Vector2PrecompiledTemplates.cpp
            #Math/MathConstants.hpp
            #Random/RandomGenerator.cpp
            #Random/RandomGenerator.hpp
            #Random/RandomGenerator.inl
        )

## Dependencies
add_dependencies(Utility Date)

## Prefix
set_target_properties(Utility PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Utility PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Utility PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

########################################################################################################################