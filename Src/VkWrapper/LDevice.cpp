#include "LDevice.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

LDevice::LDevice(const SuitablePDevice& device, const ValidationLayers& layers)
{
    TraceIt;

    const auto queueCreateInfo = device.GetQueueFamilyIndices().CreateInfo();

    // Physical device features that are gonna be used
    VkPhysicalDeviceFeatures deviceFeatures{};

    // Fill create info
    VkDeviceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfo.size()),
        .pQueueCreateInfos = queueCreateInfo.data(),
#ifndef NDEBUG
        .enabledLayerCount = static_cast<uint32_t>(layers.GetLayers().size()),
        .ppEnabledLayerNames = layers.GetLayers().data(),
#else
        .enabledLayerCount = 0,
#endif
        .enabledExtensionCount = static_cast<uint32_t>(device.GetRequiredDeviceExtensions().size()),
        .ppEnabledExtensionNames = device.GetRequiredDeviceExtensions().data(),
        .pEnabledFeatures = &deviceFeatures
    };

    Assert(vkCreateDevice(device.GetPDevice().GetHandle(), &createInfo, nullptr, &_device) == VK_SUCCESS,
           "Failed to create logical device");

    // Create all queues
    vkGetDeviceQueue(_device, device.GetQueueFamilyIndices().GetGraphicsFamily().value(), 0, &_graphicsQueue);
    vkGetDeviceQueue(_device, device.GetQueueFamilyIndices().GetPresentFamily().value(), 0, &_presentQueue);
}

// ---------------------------------------------------------------------------------------------------------------------

LDevice::~LDevice()
{
    vkDestroyDevice(_device, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkDevice LDevice::GetHandle() const
{
    return _device;
}

// ---------------------------------------------------------------------------------------------------------------------

VkQueue LDevice::GetGraphicsQueue() const
{
    return _graphicsQueue;
}

// ---------------------------------------------------------------------------------------------------------------------

VkQueue LDevice::GetPresentQueue() const
{
    return _presentQueue;
}

// ---------------------------------------------------------------------------------------------------------------------