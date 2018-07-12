cmake_minimum_required(VERSION 3.10)
project(Core)

set(Src ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

include_directories(${Src}/)

add_library(Core
            ${Src}/Core/Components/Base/BaseComponent.cpp
            ${Src}/Core/Components/Base/BaseComponent.hpp
            ${Src}/Core/Components/Base/BaseDataComponent.cpp
            ${Src}/Core/Components/Base/BaseDataComponent.hpp
            ${Src}/Core/Components/Base/BaseLogicComponent.cpp
            ${Src}/Core/Components/Base/BaseLogicComponent.hpp
            ${Src}/Core/Components/Utility/RenderablesCompare.cpp
            ${Src}/Core/Components/Utility/RenderablesCompare.hpp
            ${Src}/Core/Components/RenderableComponent.cpp
            ${Src}/Core/Components/RenderableComponent.hpp
            ${Src}/Core/Components/TransformComponent.cpp
            ${Src}/Core/Components/TransformComponent.hpp
            ${Src}/Core/Scene/BaseScene.cpp
            ${Src}/Core/Scene/BaseScene.hpp
            ${Src}/Core/Scene/BaseSceneInterface.hpp
            ${Src}/Core/Scene/SceneMap.cpp
            ${Src}/Core/Scene/SceneMap.hpp
            ${Src}/Core/Scene/SceneMapSystemInterface.hpp
            ${Src}/Core/Scene/SceneObject.cpp
            ${Src}/Core/Scene/SceneObject.hpp
            ${Src}/Core/Scene/SceneObject.inl)

set_target_properties(Core PROPERTIES PREFIX "")