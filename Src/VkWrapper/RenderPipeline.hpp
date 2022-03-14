#pragma once
#include <vector>
#include <memory>
#include <VkWrapper/LDevice.hpp>
#include <VkWrapper/SwapChain.hpp>
#include <VkWrapper/SwapChainImageViews.hpp>
#include <VkWrapper/RenderPass.hpp>
#include <VkWrapper/GraphicsPipeline.hpp>
#include <VkWrapper/Framebuffers.hpp>
#include <VkWrapper/CommandPool.hpp>
#include <VkWrapper/Vertex/VertexBufferArray.hpp>
#include <VkWrapper/CommandBuffers.hpp>
#include <VkWrapper/Memory/Semaphore.hpp>
#include <VkWrapper/Memory/Fence.hpp>
#include "VkWrapper/Shader/ShaderManager.hpp"

namespace C2D::VkWrapper
{
    class RenderPipeline final
    {
    public:
        RenderPipeline(const std::unique_ptr<LDevice>& lDevice,
                       const SuitablePDevice& suitablePDevice,
                       std::reference_wrapper<std::unique_ptr<ShaderManager>> shaderManager,
                       std::reference_wrapper<std::unique_ptr<SwapChain>> swapChain,
                       std::reference_wrapper<std::unique_ptr<SwapChainImageViews>> swapChainImageViews);

        void ResetCommandPool();

        void Clean();

        void Recreate(std::reference_wrapper<std::unique_ptr<SwapChain>> swapChain,
                      std::reference_wrapper<std::unique_ptr<SwapChainImageViews>> swapChainImageViews);

        VkResult DrawFrame();

    private:
        void CreateNewRenderPipeline();

        const std::unique_ptr<LDevice>& _lDevice;
        const SuitablePDevice& _suitablePDevice;
        std::reference_wrapper<std::unique_ptr<ShaderManager>> _shaderManager;
        std::reference_wrapper<std::unique_ptr<SwapChain>> _swapChain;
        std::reference_wrapper<std::unique_ptr<SwapChainImageViews>> _swapChainImageViews;

        std::unique_ptr<RenderPass> _renderPass;
        std::vector<std::unique_ptr<GraphicsPipeline>> _graphicsPipelines;
        std::unique_ptr<CommandPool> _commandPool;
        std::unique_ptr<CommandBuffers> _commandBuffers;
        std::unique_ptr<Framebuffers> _framebuffers;
        std::vector<std::unique_ptr<Semaphore>> _imageAvailableSemaphores;
        std::vector<std::unique_ptr<Semaphore>> _renderFinishedSemaphores;
        std::vector<std::unique_ptr<Fence>> _inFlightFences;
        std::vector<VkFence> _imageInFlight;
        size_t _currentFrame = 0;
    };
}