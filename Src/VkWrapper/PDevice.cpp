#include "PDevice.hpp"
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

PDevice::PDevice(VkPhysicalDevice device)
: _device(device)
{
    TraceIt;

    vkGetPhysicalDeviceProperties(device, &_properties);
    vkGetPhysicalDeviceMemoryProperties(device, &_memoryProperties);
    vkGetPhysicalDeviceFeatures(device, &_features);

    // Get extensions
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    _extensions.resize(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, _extensions.data());

    CalcScore();
}

// ---------------------------------------------------------------------------------------------------------------------

PDevice::PDevice(const PDevice& other) = default;

// ---------------------------------------------------------------------------------------------------------------------

PDevice::PDevice(PDevice&& other) noexcept
: _device(other._device)
, _properties(other._properties)
, _memoryProperties(other._memoryProperties)
, _features(other._features)
, _extensions(std::move(other._extensions))
, _score(other._score)
{ }

// ---------------------------------------------------------------------------------------------------------------------

PDevice& PDevice::operator=(const PDevice& other)
{
    if (this != &other)
    {
        _device = other._device;
        _properties = other._properties;
        _memoryProperties = other._memoryProperties;
        _features = other._features;
        _extensions = other._extensions;
        _score = other._score;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

PDevice& PDevice::operator=(PDevice&& other) noexcept
{
    _device = other._device;
    _properties = other._properties;
    _memoryProperties = other._memoryProperties;
    _features = other._features;
    _extensions = std::move(other._extensions);
    _score = other._score;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

VkPhysicalDevice PDevice::GetHandle() const
{
    return _device;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkPhysicalDeviceProperties& PDevice::GetProperties() const
{
    return _properties;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkPhysicalDeviceMemoryProperties& PDevice::GetMemoryProperties() const
{
    return _memoryProperties;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkPhysicalDeviceFeatures& PDevice::GetFeatures() const
{
    return _features;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VkExtensionProperties>& PDevice::GetExtensions() const
{
    return _extensions;
}

// ---------------------------------------------------------------------------------------------------------------------

uint32_t PDevice::GetScore() const
{
    return _score;
}

// ---------------------------------------------------------------------------------------------------------------------

bool PDevice::operator<(const PDevice& other) const
{
    return _score < other._score;
}

// ---------------------------------------------------------------------------------------------------------------------

void PDevice::CalcScore()
{
    if (!_features.geometryShader)
    {
        return;
    }

    if (_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        _score += 1000;
    }
    _score += _properties.limits.maxImageDimension2D;
}

// ---------------------------------------------------------------------------------------------------------------------