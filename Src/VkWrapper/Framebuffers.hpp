#pragma once
#include <VkWrapper/SwapChainImageViews.hpp>

namespace VkWrapper
{
    class Framebuffers final
    {
    public:
        Framebuffers(VkDevice lDevice,
                     const SwapChainImageViews& swapChainImageViews,
                     VkRenderPass renderPass,
                     VkExtent2D swapChainExtent);
        ~Framebuffers();

        [[nodiscard]]
        const std::vector<VkFramebuffer>& GetFramebuffers() const;

    private:
        std::vector<VkFramebuffer> _framebuffers;
        VkDevice _lDevice;
    };
}