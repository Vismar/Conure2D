#include "DebugMessenger.hpp"
#include <Logger/Logger.hpp>
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    Logger::Level GetLogLevelForMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity)
    {
        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
        {
            return Logger::Level::Verbose;
        }

        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            return Logger::Level::Info;
        }

        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            return Logger::Level::Warning;
        }

        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            return Logger::Level::Error;
        }

        return Logger::Level::Critical;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

VkDebugUtilsMessengerCreateInfoEXT DebugMessenger::_createInfo{};

// ---------------------------------------------------------------------------------------------------------------------

DebugMessenger::DebugMessenger(const Context& context)
: _context(context)
{
    TraceIt;

    const auto createInfo = GetCreateInfo();
    VkResult result = VK_ERROR_EXTENSION_NOT_PRESENT;

    auto function = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_context.GetHandle(),
                                                                               "vkCreateDebugUtilsMessengerEXT");
    if (function != nullptr)
    {
        result = function(_context.GetHandle(), &createInfo, nullptr, &_debugMessenger);
    }

    Assert(result == VK_SUCCESS, "Failed to set up debug messenger");
}

// ---------------------------------------------------------------------------------------------------------------------

DebugMessenger::~DebugMessenger()
{
    auto function = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(_context.GetHandle(),
                                                                                "vkDestroyDebugUtilsMessengerEXT");
    if (function != nullptr)
    {
        function(_context.GetHandle(), _debugMessenger, nullptr);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

const VkDebugUtilsMessengerCreateInfoEXT& DebugMessenger::GetCreateInfo()
{
    if (_createInfo.pfnUserCallback == nullptr)
    {
        _createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        _createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        _createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                  VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        _createInfo.pfnUserCallback = DebugCallback;
        _createInfo.pUserData = nullptr;
    }

    Assert(_createInfo.pfnUserCallback != nullptr, "Create info for debug messanger was not created");

    return _createInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                             const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                                                             void* userData)
{
    Logger::Log(GetLogLevelForMessage(messageSeverity), callbackData->pMessage, "Vulkan debug messenger");
    return VK_FALSE;
}

// ---------------------------------------------------------------------------------------------------------------------