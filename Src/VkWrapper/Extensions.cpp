#include "Extensions.hpp"
#include <cstring>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <Logger/Logger.hpp>
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Extensions::Extensions()
{
    TraceIt;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    _requiredExtensions = std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
#ifndef NDEBUG
    _requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    Assert(CheckSupport(), "Not all required extensions are present");
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<const char*>& Extensions::GetExtensions() const
{
    return _requiredExtensions;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Extensions::CheckSupport() const
{
    // Get number of available extensions from Vulkan
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    // Get available extensions from Vulkan
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Check if available extensions contain all required ones
    bool allPresent(true);
    for (const auto* requiredExtension : _requiredExtensions)
    {
        bool found(false);
        for (const auto& extension : extensions)
        {
            if (std::strcmp(requiredExtension, extension.extensionName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::string errorMessage = "- NOT PRESENT - ";
            errorMessage += requiredExtension;
            LOG_CRITICAL(errorMessage);
            allPresent = false;
        }
    }

    return allPresent;
}

// ---------------------------------------------------------------------------------------------------------------------