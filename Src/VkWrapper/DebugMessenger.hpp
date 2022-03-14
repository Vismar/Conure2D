#pragma once
#include <vulkan/vulkan.h>
#include <VkWrapper/Context.hpp>

namespace C2D::VkWrapper
{
    class DebugMessenger final
    {
    public:
        explicit DebugMessenger(const Context& context);
        ~DebugMessenger();

        static const VkDebugUtilsMessengerCreateInfoEXT& GetCreateInfo();

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                                                            void* userData);

        const Context& _context;
        static VkDebugUtilsMessengerCreateInfoEXT _createInfo;
        VkDebugUtilsMessengerEXT _debugMessenger{};
    };
}