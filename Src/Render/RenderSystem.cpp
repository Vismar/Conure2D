#include "RenderSystem.hpp"
#include <VkWrapper/Shader/ShaderManager.hpp>
#include <VkWrapper/Renderer/Renderer.hpp>
#include <VkWrapper/Renderer/RenderMediator.hpp>

using namespace C2D;

// ---------------------------------------------------------------------------------------------------------------------

RenderSystem::RenderSystem(std::reference_wrapper<std::unique_ptr<GLFWWrapper::Window>> window,
                           const std::vector<std::string>& shaderNames)
{
    _shaderManager = std::make_unique<VkWrapper::ShaderManager>();
    // Prepare shaders
    for (const auto& shaderName : shaderNames)
    {
        _shaderManager->AddShader(shaderName);
    }
    _renderer = std::make_unique<VkWrapper::Renderer>(window,
                                                      std::ref(_shaderManager),
                                                      "");
}

// ---------------------------------------------------------------------------------------------------------------------

RenderSystem::~RenderSystem() = default;

// ---------------------------------------------------------------------------------------------------------------------

void RenderSystem::ResetCommandPool()
{
    _renderer->WaitForCommandBuffersAndResetThem();
}

// ---------------------------------------------------------------------------------------------------------------------

std::shared_ptr<VkWrapper::IRenderMediator> RenderSystem::CreateRenderMediator(const std::string& shaderName)
{
    auto callback = [renderer = _renderer.get()](auto&& vertices)
    {
        return renderer->CreateVertexBuffer(std::forward<decltype(vertices)>(vertices));
    };

    auto renderMediator = std::make_shared<VkWrapper::RenderMediator>(std::ref(_shaderManager->GetPipelineShader(shaderName)),
                                                                      std::move(callback));
    renderMediator->Register();

    return renderMediator;
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderSystem::DrawFrame()
{
    _renderer->DrawFrame();
}

// ---------------------------------------------------------------------------------------------------------------------