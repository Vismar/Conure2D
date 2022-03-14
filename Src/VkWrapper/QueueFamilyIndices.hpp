#pragma once
#include <set>
#include <VkWrapper/PDevice.hpp>
#include <VkWrapper/Surface.hpp>

namespace C2D::VkWrapper
{
    class QueueFamilyIndices final
    {
    public:
        explicit QueueFamilyIndices(VkPhysicalDevice device, const Surface& surface);
        QueueFamilyIndices(const QueueFamilyIndices& other);
        QueueFamilyIndices(QueueFamilyIndices&& other) noexcept;
        QueueFamilyIndices& operator=(const QueueFamilyIndices& other);
        QueueFamilyIndices& operator=(QueueFamilyIndices&& other) noexcept;

        [[nodiscard]]
        bool IsComplete() const;

        [[nodiscard]]
        const std::optional<uint32_t>& GetGraphicsFamily() const;

        [[nodiscard]]
        const std::optional<uint32_t>& GetPresentFamily() const;

        [[nodiscard]]
        std::vector<VkDeviceQueueCreateInfo> CreateInfo() const;

        const float graphicsPriority = 1.0f;
        const float presentPriority = 1.0f;

    private:
        struct QueueData
        {
            uint32_t index;
            float priority;

            bool operator<(const QueueData& other) const;
        };

        std::optional<uint32_t> _graphicsFamily;
        std::optional<uint32_t> _presentFamily;
        std::set<QueueData> _uniqueFamilies;
    };
}