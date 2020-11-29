cmake_minimum_required(VERSION 3.9)
project(VkWrapper)

########################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build static library
add_library(VkWrapper STATIC
            Application.hpp
            Application.cpp
            ValidationLayers.hpp
            ValidationLayers.cpp
            Extensions.hpp
            Extensions.cpp
            Context.hpp
            Context.cpp
            PDevice.hpp
            PDevice.cpp
            DebugMessenger.hpp
            DebugMessenger.cpp
            Surface.hpp
            Surface.cpp
            QueueFamilyIndices.hpp
            QueueFamilyIndices.cpp
            SwapChainDetails.hpp
            SwapChainDetails.cpp
            SuitablePDevice.hpp
            SuitablePDevice.cpp
            LDevice.hpp
            LDevice.cpp
            Shader.hpp
            Shader.cpp
            PipelineShader.hpp
            PipelineShader.cpp
            ShaderManager.hpp
            ShaderManager.cpp
            SwapChain.hpp
            SwapChain.cpp
            SwapChainImageViews.hpp
            SwapChainImageViews.cpp
            RenderPass.hpp
            RenderPass.cpp
            GraphicsPipeline.hpp
            GraphicsPipeline.cpp
            Framebuffers.hpp
            Framebuffers.cpp
            CommandPool.hpp
            CommandPool.cpp
            CommandBuffers.hpp
            CommandBuffers.cpp
            Semaphore.hpp
            Semaphore.cpp
            Fence.hpp
            Fence.cpp
            RenderPipeline.hpp
            RenderPipeline.cpp)

## Dependencies
add_dependencies(VkWrapper Utility Logger Tracer GLFWWrapper GLM)
target_link_libraries(VkWrapper Utility Logger Tracer GLFWWrapper ${Vulkan_LIBRARY})

## Prefix
set_target_properties(VkWrapper PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(VkWrapper PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(VkWrapper PROPERTIES RELEASE_POSTFIX "-r")
endif ()

########################################################################################################################