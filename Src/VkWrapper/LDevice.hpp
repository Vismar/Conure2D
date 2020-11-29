#pragma once
#include <VkWrapper/SuitablePDevice.hpp>
#include <VkWrapper/ValidationLayers.hpp>

namespace VkWrapper
{
    class LDevice final
    {
    public:
        LDevice(const SuitablePDevice& device, const ValidationLayers& layers);
        ~LDevice();

        [[nodiscard]]
        VkDevice GetHandle() const;

        [[nodiscard]]
        VkQueue GetGraphicsQueue() const;

        [[nodiscard]]
        VkQueue GetPresentQueue() const;

    private:
        VkQueue _graphicsQueue{};
        VkQueue _presentQueue{};
        VkDevice _device{};
    };
}