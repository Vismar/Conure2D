#pragma once
#include <string>
#include <VkWrapper/ValidationLayers.hpp>
#include <VkWrapper/Extensions.hpp>
#include <VkWrapper/Context.hpp>
#ifndef NDEBUG
#include <VkWrapper/DebugMessenger.hpp>
#endif
#include <VkWrapper/Surface.hpp>
#include <VkWrapper/SuitablePDevice.hpp>
#include <VkWrapper/Shader/ShaderManager.hpp>
#include <VkWrapper/LDevice.hpp>
#include <VkWrapper/SwapChain.hpp>
#include <VkWrapper/SwapChainImageViews.hpp>
#include <VkWrapper/RenderPipeline.hpp>

namespace C2D::VkWrapper
{
    class Renderer final
    {
    public:
        Renderer(std::reference_wrapper<std::unique_ptr<GLFWWrapper::Window>> window,
                 std::reference_wrapper<std::unique_ptr<ShaderManager>> shaderManager,
                 std::string_view pDeviceName);
        ~Renderer();

        void WaitForCommandBuffersAndResetThem();


        [[nodiscard]]
        VertexBuffer CreateVertexBuffer(std::vector<Vertex>&& vertices);
        void DrawFrame();

    private:
        void OnFrameBufferResized();

        void CreateNewLogicalDevice();
        void CreateNewSwapChain();
        void RecreateSwapChain();
        void CreateRenderPipeline();

        std::reference_wrapper<std::unique_ptr<GLFWWrapper::Window>> _window;
        ValidationLayers _validationLayers;
        Extensions _extensions;
        Context _context;
#ifndef NDEBUG
        DebugMessenger _debugMessenger;
#endif
        Surface _surface;
        std::reference_wrapper<std::unique_ptr<ShaderManager>> _shaderManager;
        std::vector<SuitablePDevice> _suitableDevices;
        size_t _selectedSuitableDevice;
        std::unique_ptr<LDevice> _lDevice;

        bool _mustRecreateSwapChain = false;
        std::unique_ptr<SwapChain> _swapChain;
        std::unique_ptr<SwapChainImageViews> _swapChainImageViews;

        std::unique_ptr<RenderPipeline> _renderPipeline;
    };
}