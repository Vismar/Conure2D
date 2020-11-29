#pragma once
#include <VkWrapper/ValidationLayers.hpp>
#include <VkWrapper/Extensions.hpp>
#include <VkWrapper/PDevice.hpp>

namespace VkWrapper
{
    class Context final
    {
    public:
        Context(const ValidationLayers& validationLayers, const Extensions& extensions);
        ~Context();

        [[nodiscard]]
        VkInstance GetHandle() const;

        [[nodiscard]]
        const std::vector<PDevice>& GetPhysicalDevices() const;

    private:
        void InitPhysicalDevices();

        VkInstance _instance{};
        std::vector<PDevice> _physicalDevices;
    };
}