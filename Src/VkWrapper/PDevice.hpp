#pragma once
#include <vector>
#include <vulkan/vulkan.h>

namespace C2D::VkWrapper
{
    class PDevice final
    {
    public:
        explicit PDevice(VkPhysicalDevice device);
        PDevice(const PDevice& other);
        PDevice(PDevice&& other) noexcept;

        PDevice& operator=(const PDevice& other);
        PDevice& operator=(PDevice&& other) noexcept;

        [[nodiscard]]
        VkPhysicalDevice GetHandle() const;

        [[nodiscard]]
        const VkPhysicalDeviceProperties& GetProperties() const;

        [[nodiscard]]
        const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const;

        [[nodiscard]]
        const VkPhysicalDeviceFeatures& GetFeatures() const;

        [[nodiscard]]
        const std::vector<VkExtensionProperties>& GetExtensions() const;

        [[nodiscard]]
        uint32_t GetScore() const;

        bool operator<(const PDevice& other) const;

    private:
        void CalcScore();

        VkPhysicalDevice _device = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties _properties{};
        VkPhysicalDeviceMemoryProperties _memoryProperties{};
        VkPhysicalDeviceFeatures _features{};
        std::vector<VkExtensionProperties> _extensions;
        uint32_t _score{};
    };
}