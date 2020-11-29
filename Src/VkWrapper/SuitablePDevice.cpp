#include "SuitablePDevice.hpp"
#include <cstring>
#include <Logger/Logger.hpp>
#include <Utility/Assert.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

SuitablePDevice::SuitablePDevice(const PDevice& device,
                                 const Surface& surface,
                                 QueueFamilyIndices&& queueFamilyIndices,
                                 const std::vector<const char*>& requiredExtensions)
: _device(device)
, _surface(surface)
, _queueFamilyIndices(std::move(queueFamilyIndices))
, _requiredDeviceExtensions(requiredExtensions)
{ }

// ---------------------------------------------------------------------------------------------------------------------

const PDevice& SuitablePDevice::GetPDevice() const
{
    return _device;
}

// ---------------------------------------------------------------------------------------------------------------------

const QueueFamilyIndices& SuitablePDevice::GetQueueFamilyIndices() const
{
    return _queueFamilyIndices;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<const char*>& SuitablePDevice::GetRequiredDeviceExtensions() const
{
    return _requiredDeviceExtensions;
}

// ---------------------------------------------------------------------------------------------------------------------

SwapChainDetails SuitablePDevice::GetSwapChainDetails() const
{
    return SwapChainDetails(_device.GetHandle(), _surface.GetHandle());
}

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    const std::vector<const char*> requiredDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

// ---------------------------------------------------------------------------------------------------------------------

    bool CheckDeviceExtensionSupport(const PDevice& pDevice)
    {
        bool allPresent(true);
        for (const auto& requiredExtension : requiredDeviceExtensions)
        {
            bool found(false);
            for (const auto& extension : pDevice.GetExtensions())
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
                Logger::LogCritical(errorMessage, __PRETTY_FUNCTION__);
                allPresent = false;
            }
        }

        return allPresent;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<SuitablePDevice> VkWrapper::GetSuitablePDevicesForSurface(const std::vector<PDevice>& pDevices,
                                                                      const Surface& surface)
{
    std::vector<SuitablePDevice> suitableDevices;
    for (const auto& device : pDevices)
    {
        QueueFamilyIndices queueFamilyIndices(device.GetHandle(), surface);
        SwapChainDetails swapChainDetails(device.GetHandle(), surface.GetHandle());
        if (queueFamilyIndices.IsComplete() && CheckDeviceExtensionSupport(device) && swapChainDetails.IsAdequate())
        {
            suitableDevices.emplace_back(SuitablePDevice(device,
                                                         surface,
                                                         std::move(queueFamilyIndices),
                                                         requiredDeviceExtensions));
        }
    }

    Assert(!suitableDevices.empty(), "There are no suitable devices for the specified surface");

    return suitableDevices;
}

// ---------------------------------------------------------------------------------------------------------------------