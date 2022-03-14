#include "Context.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>
#include <VkWrapper/DebugMessenger.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    VkApplicationInfo CreateAppInfo()
    {
        VkApplicationInfo appInfo =
        {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            // TODO: Get window title to use it as application name
            .pApplicationName = "Conure2D",
            // TODO: Get application version to use it here
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "Conure2D",
            // TODO: Get engine version to use it here
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0
        };

        return appInfo;
    }

// ---------------------------------------------------------------------------------------------------------------------

    VkInstanceCreateInfo CreateInstanceInfo(const VkApplicationInfo& appInfo,
                                            const std::vector<const char*>& validationLayers,
                                            const std::vector<const char*>& extensions)
    {
        VkInstanceCreateInfo instanceInfo =
        {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo,
            // Set layers
#ifndef NDEBUG
            .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
            .ppEnabledLayerNames = validationLayers.data(),
#endif
            // Set extensions
            .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
            .ppEnabledExtensionNames = extensions.data()
        };

        return instanceInfo;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

Context::Context(const ValidationLayers& validationLayers, const Extensions& extensions)
{
    TraceIt;

    const auto appInfo = CreateAppInfo();
    auto instanceInfo = CreateInstanceInfo(appInfo, validationLayers.GetLayers(), extensions.GetExtensions());
#ifndef NDEBUG
    auto debugCreateInfo = DebugMessenger::GetCreateInfo();
    instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
#endif

    // Create VkInstance
    Assert(vkCreateInstance(&instanceInfo, nullptr, &_instance) == VK_SUCCESS,
           "Failed to create instance");

    // Initialize all physical devices that supports Vulkan
    InitPhysicalDevices();
}

// ---------------------------------------------------------------------------------------------------------------------

Context::~Context()
{
    vkDestroyInstance(_instance, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkInstance Context::GetHandle() const
{
    return _instance;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<PDevice>& Context::GetPhysicalDevices() const
{
    return _physicalDevices;
}

// ---------------------------------------------------------------------------------------------------------------------

void Context::InitPhysicalDevices()
{
    uint32_t deviceCount(0);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

    Assert(deviceCount != 0, "There are no GPUs with Vulkan support");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        _physicalDevices.emplace_back(PDevice(device));
    }

    // Sort physical devices in ascending order
    std::sort(_physicalDevices.begin(), _physicalDevices.end());
}

// ---------------------------------------------------------------------------------------------------------------------