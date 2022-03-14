#pragma once
#include <VkWrapper/QueueFamilyIndices.hpp>
#include <VkWrapper/SwapChainDetails.hpp>

namespace C2D::VkWrapper
{
    class SuitablePDevice final
    {
    public:
        SuitablePDevice(const PDevice& device,
                        const Surface& surface,
                        QueueFamilyIndices&& queueFamilyIndices,
                        const std::vector<const char*>& requiredExtensions);

        [[nodiscard]]
        const PDevice& GetPDevice() const;

        [[nodiscard]]
        const QueueFamilyIndices& GetQueueFamilyIndices() const;

        [[nodiscard]]
        const std::vector<const char*>& GetRequiredDeviceExtensions() const;

        [[nodiscard]]
        SwapChainDetails GetSwapChainDetails() const;

    private:
        const PDevice& _device;
        const Surface& _surface;
        QueueFamilyIndices _queueFamilyIndices;
        const std::vector<const char*>& _requiredDeviceExtensions;
    };

    std::vector<SuitablePDevice> GetSuitablePDevicesForSurface(const std::vector<PDevice>& pDevices,
                                                               const Surface& surface);
}

