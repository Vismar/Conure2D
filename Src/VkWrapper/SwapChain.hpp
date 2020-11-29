#pragma once
#include <VkWrapper/SuitablePDevice.hpp>
#include <GLFWWrapper/Window.hpp>

namespace VkWrapper
{
    class SwapChain final
    {
    public:
        SwapChain(VkDevice lDevice,
                  VkSurfaceKHR surface,
                  const SuitablePDevice& pDevice,
                  const GLFWWrapper::Window& window);
        ~SwapChain();

        [[nodiscard]]
        VkFormat GetImageFormat() const;

        [[nodiscard]]
        const VkExtent2D& GetExtent() const;

        [[nodiscard]]
        const std::vector<VkImage>& GetImages() const;

        [[nodiscard]]
        VkSwapchainKHR GetHandle() const;

    private:
        static const VkSurfaceFormatKHR& ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
        static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& presentModes);
        static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                           const GLFWWrapper::Window& window);

        VkDevice _lDevice;
        VkFormat _imageFormat{};
        VkExtent2D _extent{};
        std::vector<VkImage> _images;
        VkSwapchainKHR _swapChain{};
    };
}