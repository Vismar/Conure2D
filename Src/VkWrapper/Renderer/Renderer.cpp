#include "Renderer.hpp"
#include <Utility/Assert.hpp>
#include <Logger/Logger.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    size_t SelectSuitableDevice(std::string_view pDeviceName, const std::vector<SuitablePDevice>& suitablePDevices)
    {
        if (pDeviceName.empty())
        {
            return suitablePDevices.size() - 1;
        }

        for (size_t i = 0; i > suitablePDevices.size(); ++i)
        {
            if (suitablePDevices[i].GetPDevice().GetProperties().deviceName == pDeviceName)
            {
                return i;
            }
        }

        return suitablePDevices.size() - 1;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

Renderer::Renderer(std::reference_wrapper<std::unique_ptr<GLFWWrapper::Window>> window,
                   std::reference_wrapper<std::unique_ptr<ShaderManager>> shaderManager,
                   std::string_view pDeviceName)
: _window(window)
, _context(_validationLayers, _extensions)
#ifndef NDEBUG
, _debugMessenger(_context)
#endif
, _surface(_context, *_window.get())
, _shaderManager(shaderManager)
, _suitableDevices(GetSuitablePDevicesForSurface(_context.GetPhysicalDevices(), _surface))
, _selectedSuitableDevice(SelectSuitableDevice(pDeviceName, _suitableDevices))
{
    _window.get()->AddFramebufferResizedCallback([this] { OnFrameBufferResized(); });

    CreateNewLogicalDevice();
    CreateNewSwapChain();

    CreateRenderPipeline();
}

// ---------------------------------------------------------------------------------------------------------------------

Renderer::~Renderer()
{
    vkDeviceWaitIdle(_lDevice->GetHandle());
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::WaitForCommandBuffersAndResetThem()
{
    vkDeviceWaitIdle(_lDevice->GetHandle());
    //_renderPipeline->ResetCommandPool();
}

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer Renderer::CreateVertexBuffer(std::vector<Vertex>&& vertices)
{
    return VertexBuffer{_lDevice->GetHandle(),
                        std::ref(_suitableDevices[_selectedSuitableDevice]),
                        std::move(vertices)};
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::DrawFrame()
{
    auto result = _renderPipeline->DrawFrame();
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _mustRecreateSwapChain)
    {
        // In case if the window was minimized we should wait until it will be restored
        auto [width, height] = _window.get()->GetFrameBufferSize();
        while (width == 0 || height == 0)
        {
            glfwWaitEvents();
            auto [newWidth, newHeight] = _window.get()->GetFrameBufferSize();
            width = newWidth;
            height = newHeight;
        }

        vkDeviceWaitIdle(_lDevice->GetHandle());
        RecreateSwapChain();
        return;
    }

    Assert(result == VK_SUCCESS, "Failed to obtain or present image");
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::OnFrameBufferResized()
{
    _mustRecreateSwapChain = true;
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::CreateNewLogicalDevice()
{
    _lDevice = std::make_unique<LDevice>(_suitableDevices[_selectedSuitableDevice], _validationLayers);
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::CreateNewSwapChain()
{
    _swapChain = std::make_unique<SwapChain>(_lDevice->GetHandle(),
                                             _surface.GetHandle(),
                                             _suitableDevices[_selectedSuitableDevice],
                                             *_window.get());
    _swapChainImageViews = std::make_unique<SwapChainImageViews>(_lDevice->GetHandle(), *_swapChain);
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::RecreateSwapChain()
{
    LOG_INFO("Start of the swap chain recreation");

    _mustRecreateSwapChain = false;
    _swapChain.reset();
    _swapChainImageViews.reset();
    CreateNewSwapChain();
    _renderPipeline->Clean();
    _renderPipeline->Recreate(std::ref(_swapChain), std::ref(_swapChainImageViews));

    LOG_INFO("End of the swap chain recreation");
}

// ---------------------------------------------------------------------------------------------------------------------

void Renderer::CreateRenderPipeline()
{
    _renderPipeline = std::make_unique<RenderPipeline>(_lDevice,
                                                       _suitableDevices[_selectedSuitableDevice],
                                                       _shaderManager,
                                                       std::ref(_swapChain),
                                                       std::ref(_swapChainImageViews));
}

// ---------------------------------------------------------------------------------------------------------------------