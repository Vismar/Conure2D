#pragma once
#include <memory>
#include <vector>

namespace C2D
{
    namespace GLFWWrapper
    {
        class Window;
    }

    namespace VkWrapper
    {
        class ShaderManager;
        class IRenderMediator;


        class Renderer;
    }

    class RenderSystem final
    {
    public:
        explicit RenderSystem(std::reference_wrapper<std::unique_ptr<GLFWWrapper::Window>> window,
                              const std::vector<std::string>& shaderNames);
        ~RenderSystem();

        void ResetCommandPool();

        std::shared_ptr<VkWrapper::IRenderMediator> CreateRenderMediator(const std::string& shaderName);

        void DrawFrame();

    private:
        std::unique_ptr<VkWrapper::ShaderManager> _shaderManager;
        std::unique_ptr<VkWrapper::Renderer> _renderer;
    };
}