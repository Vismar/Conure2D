#pragma once
#include <VkWrapper/SwapChain.hpp>

namespace VkWrapper
{
    class SwapChainImageViews final
    {
    public:
        explicit SwapChainImageViews(VkDevice lDevice, const SwapChain& swapChain);
        ~SwapChainImageViews();

        [[nodiscard]]
        const std::vector<VkImageView>& GetImageViews() const;

    private:
        VkDevice _lDevice;
        std::vector<VkImageView> _imageViews;
    };
}