cmake_minimum_required(VERSION 3.9)
project(Core)

#######################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

#######################################################################################################################
# Build static library
add_library(Core
            Components/Base/BaseComponent.cpp
            Components/Base/BaseComponent.hpp
            Components/Base/BaseDataComponent.cpp
            Components/Base/BaseDataComponent.hpp
            Components/Base/BaseLogicComponent.cpp
            Components/Base/BaseLogicComponent.hpp
            Components/Utility/CamerasCompare.cpp
            Components/Utility/CamerasCompare.hpp
            Components/Utility/RenderablesCompare.cpp
            Components/Utility/RenderablesCompare.hpp
            Components/CameraComponent.cpp
            Components/CameraComponent.hpp
            Components/RenderableComponent.cpp
            Components/RenderableComponent.hpp
            Components/TransformComponent.cpp
            Components/TransformComponent.hpp
            Scene/BaseScene.cpp
            Scene/BaseScene.hpp
            Scene/BaseSceneInterface.hpp
            Scene/SceneMap.cpp
            Scene/SceneMap.hpp
            Scene/SceneMapSystemInterface.hpp
            Scene/SceneObject.cpp
            Scene/SceneObject.hpp
            Scene/SceneObject.inl)

## Dependencies
add_dependencies(Core SFML)

## Prefix
set_target_properties(Core PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Core PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Core PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################