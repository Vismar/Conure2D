#include "RenderMediator.hpp"
#include <VkWrapper/Shader/PipelineShader.hpp>
#include <VkWrapper/Vertex/VertexBuffer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

RenderMediator::RenderMediator(std::reference_wrapper<PipelineShader> pipelineShader,
                               CreateVertexCallback&& createVertexBufferCallback)
: _pipelineShader(pipelineShader)
, _createVertexBufferCallback(createVertexBufferCallback)
{ }

// ---------------------------------------------------------------------------------------------------------------------

void RenderMediator::SetSubmitRenderCommandsCallback(SubmitRenderCommandsCallback&& submitRenderCommandsCallback)
{
    _submitRenderCommandsCallback = std::move(submitRenderCommandsCallback);
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderMediator::Delete()
{
    _pipelineShader.get().RemoveRenderMediator(_handle);
}

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer RenderMediator::CreateVertexBuffer(std::vector<Vertex>&& vertices)
{
    return _createVertexBufferCallback(std::move(vertices));
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderMediator::Register()
{
    _handle = _pipelineShader.get().AddRenderMediator(shared_from_this());
}

// ---------------------------------------------------------------------------------------------------------------------

void RenderMediator::SubmitRenderCommands(const VkCommandBuffer& commandBuffer)
{
    _submitRenderCommandsCallback(commandBuffer);
}

// ---------------------------------------------------------------------------------------------------------------------