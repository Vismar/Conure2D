#include "RenderPipeline.hpp"
#include <Utility/Assert.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    constexpr int maxFramesInFlight = 2;
}

// ---------------------------------------------------------------------------------------------------------------------

RenderPipeline::RenderPipeline(const std::unique_ptr<LDevice>& lDevice,
                               const SuitablePDevice& suitablePDevice,
                               const PipelineShader& pipelineShader,
                               std::reference_wrapper<std::unique_ptr<SwapChain>> swapChain,
                               std::reference_wrapper<std::unique_ptr<SwapChainImageViews>> swapChainImageViews)
: _lDevice(lDevice)
, _suitablePDevice(suitablePDevice)
, _pipelineShader(pipelineShader)
, _swapChain(swapChain)
, _swapChainImageViews(swapChainImageViews)
{
    CreateNewRenderPipeline();
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderPipeline::Clean()
{
    _commandBuffers.reset();
    _framebuffers.reset();
    _graphicsPipeline.reset();
    _renderPass.reset();
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderPipeline::Recreate(std::reference_wrapper<std::unique_ptr<SwapChain>> swapChain,
                              std::reference_wrapper<std::unique_ptr<SwapChainImageViews>> swapChainImageViews)
{
    _swapChain = swapChain;
    _swapChainImageViews = _swapChainImageViews;

    CreateNewRenderPipeline();
}

// ---------------------------------------------------------------------------------------------------------------------

VkResult RenderPipeline::DrawFrame()
{
    auto lDeviceHandle = _lDevice->GetHandle();

    // Wait for the current fence
    vkWaitForFences(lDeviceHandle, 1, &_inFlightFences[_currentFrame]->GetHandle(), VK_TRUE, UINT64_MAX);

    // Acquire next image and wait 'til it is ready to use
    uint32_t imageIndex;
    auto result = vkAcquireNextImageKHR(lDeviceHandle,
                                        _swapChain.get()->GetHandle(),
                                        UINT64_MAX,
                                        _imageAvailableSemaphores[_currentFrame]->GetHandle(),
                                        VK_NULL_HANDLE,
                                        &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        return result;
    }

    if (_imageInFlight[imageIndex] != VK_NULL_HANDLE)
    {
        vkWaitForFences(lDeviceHandle, 1, &_imageInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    _imageInFlight[imageIndex] = _inFlightFences[_currentFrame]->GetHandle();

    // Submitting the command buffer
    VkSemaphore waitSemaphores[] = { _imageAvailableSemaphores[_currentFrame]->GetHandle() };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSemaphore signalSemaphores[] = { _renderFinishedSemaphores[_currentFrame]->GetHandle() };
    VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = static_cast<uint32_t>(std::size(waitSemaphores)),
        .pWaitSemaphores = waitSemaphores,
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = 1,
        .pCommandBuffers = &_commandBuffers->GetCommandBuffers()[imageIndex],
        .signalSemaphoreCount = static_cast<uint32_t>(std::size(signalSemaphores)),
        .pSignalSemaphores = signalSemaphores
    };
    vkResetFences(lDeviceHandle, 1, &_inFlightFences[_currentFrame]->GetHandle());
    Assert(vkQueueSubmit(_lDevice->GetGraphicsQueue(),
                         1,
                         &submitInfo,
                         _inFlightFences[_currentFrame]->GetHandle()) == VK_SUCCESS,
           "Failed to submit draw command buffer");

    // Present a new frame
    VkSwapchainKHR swapChains[] = { _swapChain.get()->GetHandle() };
    VkPresentInfoKHR presentInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = std::size(signalSemaphores),
        .pWaitSemaphores = signalSemaphores,
        .swapchainCount = std::size(swapChains),
        .pSwapchains = swapChains,
        .pImageIndices = &imageIndex,
        .pResults = nullptr
    };
    result = vkQueuePresentKHR(_lDevice->GetPresentQueue(), &presentInfo); // TODO: Handle later
    _currentFrame = (_currentFrame + 1) % maxFramesInFlight;

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderPipeline::CreateNewRenderPipeline()
{
    auto lDeviceHandle = _lDevice->GetHandle();
    auto swapChainExtent = _swapChain.get()->GetExtent();

    // Graphics
    _renderPass = std::make_unique<RenderPass>(lDeviceHandle, _swapChain.get()->GetImageFormat());
    auto renderPassHandle = _renderPass->GetHandle();
    _graphicsPipeline = std::make_unique<GraphicsPipeline>(lDeviceHandle,
                                                           _pipelineShader,
                                                           swapChainExtent,
                                                           renderPassHandle);
    _framebuffers = std::make_unique<Framebuffers>(lDeviceHandle,
                                                   *(_swapChainImageViews.get()),
                                                   renderPassHandle,
                                                   swapChainExtent);

    // Commands
    if (!_commandPool)
    {
        _commandPool = std::make_unique<CommandPool>(
                lDeviceHandle,
                _suitablePDevice.GetQueueFamilyIndices().GetGraphicsFamily().value());
    }
    _commandBuffers = std::make_unique<CommandBuffers>(lDeviceHandle,
                                                       _framebuffers->GetFramebuffers().size(),
                                                       _commandPool->GetHandle(),
                                                       renderPassHandle,
                                                       _framebuffers->GetFramebuffers(),
                                                       swapChainExtent,
                                                       _graphicsPipeline->GetHandle());

    // Clean synchronization stuff
    _imageAvailableSemaphores.clear();
    _renderFinishedSemaphores.clear();
    _inFlightFences.clear();
    _imageInFlight.clear();

    // Create synchronization stuff
    _imageAvailableSemaphores.resize(maxFramesInFlight);
    _renderFinishedSemaphores.resize(maxFramesInFlight);
    _inFlightFences.resize(maxFramesInFlight);
    _imageInFlight.resize(_swapChain.get()->GetImages().size(), VK_NULL_HANDLE);
    for (size_t i = 0; i < maxFramesInFlight; ++i)
    {
        _imageAvailableSemaphores[i] = std::make_unique<Semaphore>(lDeviceHandle);
        _renderFinishedSemaphores[i] = std::make_unique<Semaphore>(lDeviceHandle);
        _inFlightFences[i] = std::make_unique<Fence>(lDeviceHandle);
    }
}

// ---------------------------------------------------------------------------------------------------------------------