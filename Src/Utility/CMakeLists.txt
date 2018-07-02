cmake_minimum_required(VERSION 3.10)
project(Utility)

set(CMAKE_CXX_STANDARD 17)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}../../../Lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}../../../Lib")

include_directories(${dir}../)
include_directories(${dir}../../)

add_library(Utility
            Containers/AnyCallable/AnyCallable.hpp
            Containers/AnyCallable/AnyCallable.inl
            Containers/AnyCallable/AnyCallableHandler.cpp
            Containers/AnyCallable/AnyCallableHandler.hpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.cpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp
            Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.inl
            Containers/RingBuffer/RingBuffer.hpp
            Containers/RingBuffer/RingBuffer.inl
            Containers/RingBuffer/RingBufferIterator.hpp
            Containers/RingBuffer/RingBufferIterator.inl
            Containers/RingBuffer/RingBufferReverseIterator.hpp
            Containers/RingBuffer/RingBufferReverseIterator.inl
            EventSystem/Dispatcher.hpp
            EventSystem/Dispatcher.inl
            EventSystem/DispatcherInterface.hpp
            EventSystem/EventManager.cpp
            EventSystem/EventManager.hpp
            EventSystem/EventManager.inl
            IOSystem/IOSystem.cpp
            IOSystem/IOSystem.hpp
            IOSystem/IOSystemInterface.hpp
            LogSystem/LogEntry.cpp
            LogSystem/LogEntry.hpp
            LogSystem/LogSystem.cpp
            LogSystem/LogSystem.hpp
            Math/Vector2/AtomicVector2.hpp
            Math/Vector2/AtomicVector2.inl
            Math/Vector2/Vector2.hpp
            Math/Vector2/Vector2.inl
            Math/Vector2/Vector2PrecompiledTemplates.cpp
            Math/MathConstants.hpp
            Math/Vectors.hpp
            Random/RandomGenerator.cpp
            Random/RandomGenerator.hpp
            Random/RandomGenerator.inl
            Time/Time.cpp
            Time/Time.hpp
            Time/TimeSpan.cpp
            Time/TimeSpan.hpp)

set_target_properties(Utility PROPERTIES PREFIX "")