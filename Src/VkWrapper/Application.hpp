#pragma once
#include <string>
#include <vector>
#include <memory>
#include <GLFWWrapper/Window.hpp>
#include <VkWrapper/ValidationLayers.hpp>
#include <VkWrapper/Extensions.hpp>
#include <VkWrapper/Context.hpp>
#ifndef NDEBUG
#include <VkWrapper/DebugMessenger.hpp>
#endif
#include <VkWrapper/Surface.hpp>
#include <VkWrapper/SuitablePDevice.hpp>
#include <VkWrapper/Shader/ShaderManager.hpp>
#include <VkWrapper/Vertex/VertexManager.hpp>
#include <VkWrapper/LDevice.hpp>
#include <VkWrapper/SwapChain.hpp>
#include <VkWrapper/SwapChainImageViews.hpp>
#include <VkWrapper/RenderPipeline.hpp>










#include <VkWrapper/Renderer/TriangleRenderer.hpp>




namespace C2D::VkWrapper
{
    struct ApplicationConfiguration
    {
    public:
        ApplicationConfiguration(GLFWWrapper::Window& window,
                                 std::string pDeviceName,
                                 std::vector<std::string>&& shadersList);

        [[nodiscard]]
        GLFWWrapper::Window& GetWindow() const;

        [[nodiscard]]
        std::string_view GetPDeviceName() const;

        [[nodiscard]]
        const std::vector<std::string>& GetShadersList() const;

    private:
        GLFWWrapper::Window& _window;
        std::string _pDeviceName;
        const std::vector<std::string>& _shadersList;
    };

    class Application final
    {
    public:
        explicit Application(const ApplicationConfiguration& configuration);
        ~Application();

        void DrawFrame();

    private:
        void OnFrameBufferResized();

        void CreateNewLogicalDevice();
        void CreateVertexManager();
        void CreateNewSwapChain();
        void RecreateSwapChain();
        void CreateRenderPipeline(const std::string& shaderName);

        const ApplicationConfiguration& _configuration;

        ValidationLayers _validationLayers;
        Extensions _extensions;
        Context _context;
#ifndef NDEBUG
        DebugMessenger _debugMessenger;
#endif
        Surface _surface;
        ShaderManager _shaderManager;
        std::vector<SuitablePDevice> _suitableDevices;
        size_t _selectedSuitableDevice;
        std::unique_ptr<LDevice> _lDevice;
        std::unique_ptr<VertexManager> _vertexManager;

        bool _mustRecreateSwapChain = false;

        std::unique_ptr<SwapChain> _swapChain;
        std::unique_ptr<SwapChainImageViews> _swapChainImageViews;

        std::unique_ptr<RenderPipeline> _renderPipeline;




        std::shared_ptr<TriangleRenderer> _triangleRenderer;
        std::shared_ptr<TriangleRenderer> _secondTriangleRenderer;
    };
}