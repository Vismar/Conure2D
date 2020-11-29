#include "ValidationLayers.hpp"
#include <cstring>
#include <vulkan/vulkan.h>
#include <Logger/Logger.hpp>
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

ValidationLayers::ValidationLayers()
: _validationLayers({"VK_LAYER_KHRONOS_validation"})
{
    TraceIt;

#ifndef NDEBUG
    Assert(CheckSupport(), "Not all required validation layers are present");
#endif
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<const char*>& ValidationLayers::GetLayers() const
{
    return _validationLayers;
}

// ---------------------------------------------------------------------------------------------------------------------

bool ValidationLayers::CheckSupport() const
{
    // Get number of available layers from Vulkan
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    // Get available layers from Vulkan
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Check if available layers contain all required ones
    bool allPresent(true);
    for (const auto* layerName : _validationLayers)
    {
        bool found(false);
        for (const auto& layer : availableLayers)
        {
            if (std::strcmp(layerName, layer.layerName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::string errorMessage = "- NOT PRESENT - ";
            errorMessage += layerName;
            Logger::LogCritical(errorMessage, __PRETTY_FUNCTION__);
            allPresent = false;
        }
    }

    return allPresent;
}

// ---------------------------------------------------------------------------------------------------------------------