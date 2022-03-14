#pragma once
#include <VkWrapper/Renderer/IRenderMediator.hpp>
#include <list>

namespace C2D::VkWrapper
{
    class Vertex;
    class VertexBuffer;
    class PipelineShader;
    class RenderMediator;

    using RenderMediatorHandle = std::list<std::shared_ptr<RenderMediator>>::iterator;
    using SubmitRenderCommandsCallback = std::function<void(const VkCommandBuffer& commandBuffer)>;

    class RenderMediator final : public IRenderMediator, public std::enable_shared_from_this<RenderMediator>
    {
    public:
        using CreateVertexCallback = std::function<VertexBuffer(std::vector<Vertex>&& vertices)>;

        RenderMediator(std::reference_wrapper<PipelineShader> pipelineShader,
                       CreateVertexCallback&& createVertexBufferCallback);
        ~RenderMediator() = default;

        void SetSubmitRenderCommandsCallback(SubmitRenderCommandsCallback&& submitRenderCommandsCallback) final;

        void Delete() final;

        VertexBuffer CreateVertexBuffer(std::vector<Vertex>&& vertices) final;

        void Register();

        void SubmitRenderCommands(const VkCommandBuffer& commandBuffer);

    private:
        std::reference_wrapper<PipelineShader> _pipelineShader;
        SubmitRenderCommandsCallback _submitRenderCommandsCallback;
        CreateVertexCallback _createVertexBufferCallback;
        RenderMediatorHandle _handle;
    };
}