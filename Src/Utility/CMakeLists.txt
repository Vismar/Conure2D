cmake_minimum_required(VERSION 3.9)
project(Utility)

#######################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

#######################################################################################################################
# Build static library
add_library(Utility 
            Containers/AnyCallable/AnyCallable.hpp
            Containers/AnyCallable/AnyCallable.inl
            Containers/AnyCallable/AnyCallableHandler.cpp
            Containers/AnyCallable/AnyCallableHandler.hpp
            Containers/AnyCallable/BadAnyCallableCall.cpp
            Containers/AnyCallable/BadAnyCallableCall.inl
            Containers/AnyCallable/BadAnyCallableCall.hpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.cpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.inl
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueueReference.inl
            Containers/RingBuffer/RingBuffer.hpp
            Containers/RingBuffer/RingBuffer.inl
            Containers/RingBuffer/RingBufferConstIterator.inl
            Containers/RingBuffer/RingBufferConstReverseIterator.inl
            Containers/RingBuffer/RingBufferIterator.inl
            Containers/RingBuffer/RingBufferReverseIterator.inl
            EventSystem/Dispatcher.hpp
            EventSystem/Dispatcher.inl
            EventSystem/DispatcherInterface.hpp
            EventSystem/EventManager.cpp
            EventSystem/EventManager.hpp
            EventSystem/EventManager.inl
            Exception/ExceptionHandler.hpp
            IOSystem/IOSystem.cpp
            IOSystem/IOSystem.hpp
            IOSystem/IOSystemInterface.hpp
            LogSystem/LogEntry.cpp
            LogSystem/LogEntry.hpp
            LogSystem/LogSystem.cpp
            LogSystem/LogSystem.hpp
            LogSystem/LogUtilities.hpp
            Math/Vector2.hpp
            Math/Vector2.inl
            Math/Vector2PrecompiledTemplates.cpp
            Math/MathConstants.hpp
            Random/RandomGenerator.cpp
            Random/RandomGenerator.hpp
            Random/RandomGenerator.inl
            Time/Time.cpp
            Time/Time.hpp
            Time/TimeSpan.cpp
            Time/TimeSpan.hpp)

## Dependencies
add_dependencies(Utility SFML)

## Prefix
set_target_properties(Utility PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Utility PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Utility PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################