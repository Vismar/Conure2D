cmake_minimum_required(VERSION 3.10)
project(Utility)

set(Src ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

include_directories(${Src}/)

add_library(Utility 
            ${Src}/Utility/Containers/AnyCallable/AnyCallable.hpp
            ${Src}/Utility/Containers/AnyCallable/AnyCallable.inl
            ${Src}/Utility/Containers/AnyCallable/AnyCallableHandler.cpp
            ${Src}/Utility/Containers/AnyCallable/AnyCallableHandler.hpp
            ${Src}/Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.cpp
            ${Src}/Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp
            ${Src}/Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.inl
            ${Src}/Utility/Containers/RingBuffer/RingBuffer.hpp
            ${Src}/Utility/Containers/RingBuffer/RingBuffer.inl
            ${Src}/Utility/Containers/RingBuffer/RingBufferIterator.hpp
            ${Src}/Utility/Containers/RingBuffer/RingBufferIterator.inl
            ${Src}/Utility/Containers/RingBuffer/RingBufferReverseIterator.hpp
            ${Src}/Utility/Containers/RingBuffer/RingBufferReverseIterator.inl
            ${Src}/Utility/EventSystem/Dispatcher.hpp
            ${Src}/Utility/EventSystem/Dispatcher.inl
            ${Src}/Utility/EventSystem/DispatcherInterface.hpp
            ${Src}/Utility/EventSystem/EventManager.cpp
            ${Src}/Utility/EventSystem/EventManager.hpp
            ${Src}/Utility/EventSystem/EventManager.inl
            ${Src}/Utility/IOSystem/IOSystem.cpp
            ${Src}/Utility/IOSystem/IOSystem.hpp
            ${Src}/Utility/IOSystem/IOSystemInterface.hpp
            ${Src}/Utility/LogSystem/LogEntry.cpp
            ${Src}/Utility/LogSystem/LogEntry.hpp
            ${Src}/Utility/LogSystem/LogSystem.cpp
            ${Src}/Utility/LogSystem/LogSystem.hpp
            ${Src}/Utility/Math/Vector2/AtomicVector2.hpp
            ${Src}/Utility/Math/Vector2/AtomicVector2.inl
            ${Src}/Utility/Math/Vector2/Vector2.hpp
            ${Src}/Utility/Math/Vector2/Vector2.inl
            ${Src}/Utility/Math/Vector2/Vector2PrecompiledTemplates.cpp
            ${Src}/Utility/Math/MathConstants.hpp
            ${Src}/Utility/Math/Vectors.hpp
            ${Src}/Utility/Random/RandomGenerator.cpp
            ${Src}/Utility/Random/RandomGenerator.hpp
            ${Src}/Utility/Random/RandomGenerator.inl
            ${Src}/Utility/Time/Time.cpp
            ${Src}/Utility/Time/Time.hpp
            ${Src}/Utility/Time/TimeSpan.cpp
            ${Src}/Utility/Time/TimeSpan.hpp)

set_target_properties(Utility PROPERTIES PREFIX "")