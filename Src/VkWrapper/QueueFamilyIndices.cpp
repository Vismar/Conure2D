#include "QueueFamilyIndices.hpp"
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

QueueFamilyIndices::QueueFamilyIndices(VkPhysicalDevice device, const Surface& surface)
{
    TraceIt;

    // Get number of queue families
    uint32_t queueFamilyCount(0);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    // Get queue families
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    // Find graphics family
    uint32_t i(0);
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            _graphicsFamily = i;
            _uniqueFamilies.insert({i, graphicsPriority});
        }

        // Check present support
        VkBool32 presentSupport(VK_FALSE);
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface.GetHandle(), &presentSupport);
        if (presentSupport == VK_TRUE)
        {
            _presentFamily = i;
            _uniqueFamilies.insert({i, presentPriority});
        }

        // If we found all required queue families break loop
        if (IsComplete())
        {
            break;
        }

        ++i;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

QueueFamilyIndices::QueueFamilyIndices(const QueueFamilyIndices& other)
{
    _graphicsFamily = other._graphicsFamily;
    _presentFamily = other._presentFamily;
    _uniqueFamilies = other._uniqueFamilies;
}

// ---------------------------------------------------------------------------------------------------------------------

QueueFamilyIndices::QueueFamilyIndices(QueueFamilyIndices&& other) noexcept
{
    _graphicsFamily = other._graphicsFamily;
    _presentFamily = other._presentFamily;
    _uniqueFamilies = std::move(other._uniqueFamilies);
}

// ---------------------------------------------------------------------------------------------------------------------

QueueFamilyIndices& QueueFamilyIndices::operator=(const QueueFamilyIndices& other)
{
    _graphicsFamily = other._graphicsFamily;
    _presentFamily = other._presentFamily;
    _uniqueFamilies = other._uniqueFamilies;
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

QueueFamilyIndices& QueueFamilyIndices::operator=(QueueFamilyIndices&& other) noexcept
{
    _graphicsFamily = other._graphicsFamily;
    _presentFamily = other._presentFamily;
    _uniqueFamilies = std::move(other._uniqueFamilies);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

bool QueueFamilyIndices::IsComplete() const
{
    return _graphicsFamily.has_value() &&
           _presentFamily.has_value();
}

// ---------------------------------------------------------------------------------------------------------------------

const std::optional<uint32_t>& QueueFamilyIndices::GetGraphicsFamily() const
{
    return _graphicsFamily;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::optional<uint32_t>& QueueFamilyIndices::GetPresentFamily() const
{
    return _presentFamily;
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<VkDeviceQueueCreateInfo> QueueFamilyIndices::CreateInfo() const
{
    std::vector<VkDeviceQueueCreateInfo> info;

    for (const auto& queueData : _uniqueFamilies)
    {
        VkDeviceQueueCreateInfo  queueCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queueData.index,
            .queueCount = 1,
            .pQueuePriorities = &queueData.priority
        };
        info.push_back(queueCreateInfo);
    }

    return info;
}

// ---------------------------------------------------------------------------------------------------------------------

bool QueueFamilyIndices::QueueData::operator<(const QueueData& other) const
{
    return index < other.index;
}

// ---------------------------------------------------------------------------------------------------------------------