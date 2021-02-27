#include "Application.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>
#include <Logger/Logger.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

ApplicationConfiguration::ApplicationConfiguration(GLFWWrapper::Window& window,
                                                   std::string pDeviceName,
                                                   std::vector<std::string>&& shadersList)
: _window(window)
, _pDeviceName(std::move(pDeviceName))
, _shadersList(std::move(shadersList))
{ }

// ---------------------------------------------------------------------------------------------------------------------

GLFWWrapper::Window& ApplicationConfiguration::GetWindow() const
{
    return _window;
}

// ---------------------------------------------------------------------------------------------------------------------

std::string_view ApplicationConfiguration::GetPDeviceName() const
{
    return _pDeviceName;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<std::string>& ApplicationConfiguration::GetShadersList() const
{
    return _shadersList;
}

// ---------------------------------------------------------------------------------------------------------------------

namespace
{
    constexpr int maxFramesInFlight = 2;

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

Application::Application(const ApplicationConfiguration& configuration)
: _configuration(configuration)
, _context(_validationLayers, _extensions)
#ifndef NDEBUG
, _debugMessenger(_context)
#endif
, _surface(_context, _configuration.GetWindow())
, _suitableDevices(GetSuitablePDevicesForSurface(_context.GetPhysicalDevices(), _surface))
, _selectedSuitableDevice(SelectSuitableDevice(_configuration.GetPDeviceName(), _suitableDevices))
{
    _configuration.GetWindow().AddFramebufferResizedCallback([this] { OnFrameBufferResized(); });


    CreateNewLogicalDevice();
    CreateVertexManager();
    CreateNewSwapChain();

    const auto& pipelineShader = _shaderManager.GetPipelineShader("./shader");
    const VertexBufferArray& vertexBuffers = _vertexManager->GetVertexBuffers("./shader");

    CreateRenderPipeline(pipelineShader, vertexBuffers);
}

// ---------------------------------------------------------------------------------------------------------------------

Application::~Application()
{
    vkDeviceWaitIdle(_lDevice->GetHandle());
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::DrawFrame()
{
    auto result = _renderPipeline->DrawFrame();
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _mustRecreateSwapChain)
    {
        // In case if the window was minimized we should wait until it will be restored
        auto [width, height] = _configuration.GetWindow().GetFrameBufferSize();
        while (width == 0 || height == 0)
        {
            glfwWaitEvents();
            auto [newWidth, newHeight] = _configuration.GetWindow().GetFrameBufferSize();
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

void Application::OnFrameBufferResized()
{
    _mustRecreateSwapChain = true;
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::CreateNewLogicalDevice()
{
    _lDevice = std::make_unique<LDevice>(_suitableDevices[_selectedSuitableDevice], _validationLayers);
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::CreateVertexManager()
{
    _vertexManager = std::make_unique<VertexManager>(_lDevice->GetHandle(),
                                                     _suitableDevices[_selectedSuitableDevice]);
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::CreateNewSwapChain()
{
    _swapChain = std::make_unique<SwapChain>(_lDevice->GetHandle(),
                                             _surface.GetHandle(),
                                             _suitableDevices[_selectedSuitableDevice],
                                             _configuration.GetWindow());
    _swapChainImageViews = std::make_unique<SwapChainImageViews>(_lDevice->GetHandle(), *_swapChain);
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::RecreateSwapChain()
{
    Logger::LogInfo("Start of the swap chain recreation", __PRETTY_FUNCTION__);

    _mustRecreateSwapChain = false;
    _swapChain.reset();
    _swapChainImageViews.reset();
    CreateNewSwapChain();
    _renderPipeline->Clean();
    _renderPipeline->Recreate(std::ref(_swapChain), std::ref(_swapChainImageViews));

    Logger::LogInfo("End of the swap chain recreation", __PRETTY_FUNCTION__);
}

// ---------------------------------------------------------------------------------------------------------------------

void Application::CreateRenderPipeline(const PipelineShader& pipeLineShader,
                                       const VertexBufferArray& vertexBuffers)
{
    _renderPipeline = std::make_unique<RenderPipeline>(_lDevice,
                                                       _suitableDevices[_selectedSuitableDevice],
                                                       pipeLineShader,
                                                       vertexBuffers,
                                                       std::ref(_swapChain),
                                                       std::ref(_swapChainImageViews));
}

// ---------------------------------------------------------------------------------------------------------------------

