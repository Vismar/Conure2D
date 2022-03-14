#pragma once
#include <vector>
#include <vulkan/vulkan.h>

namespace C2D::VkWrapper
{
    class SwapChainDetails final
    {
    public:
        SwapChainDetails(VkPhysicalDevice pDevice, VkSurfaceKHR surface);

        [[nodiscard]]
        bool IsAdequate() const;

        [[nodiscard]]
        const VkSurfaceCapabilitiesKHR& GetCapabilities() const;

        [[nodiscard]]
        const std::vector<VkSurfaceFormatKHR>& GetFormats() const;

        [[nodiscard]]
        const std::vector<VkPresentModeKHR>& GetPresentModes() const;

    private:
        VkSurfaceCapabilitiesKHR _capabilities{};
        std::vector<VkSurfaceFormatKHR> _formats;
        std::vector<VkPresentModeKHR> _presentModes;
    };
}