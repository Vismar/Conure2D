#include "TriangleRenderer.hpp"
#include <VkWrapper/Renderer/IRenderMediator.hpp>
#include <VkWrapper/Vertex/VertexBuffer.hpp>

using namespace C2D;

// ---------------------------------------------------------------------------------------------------------------------

TriangleRenderer::TriangleRenderer(std::shared_ptr<VkWrapper::IRenderMediator>&& renderMediator)
: _renderMediator(std::move(renderMediator))
, _vertexBuffer(std::make_unique<VkWrapper::VertexBuffer>(_renderMediator->CreateVertexBuffer(
    {
        VkWrapper::Vertex
        {
            .position{0.0f, -0.5f},
            .color{1.0f, 0.0f, 0.0f}
        },
        VkWrapper::Vertex
        {
            .position{0.5f, 0.5f},
            .color{0.0f, 1.0f, 0.0f}
        },
        VkWrapper::Vertex
        {
            .position{-0.5f, 0.5f},
            .color{0.0f, 0.0f, 1.0f}
        }
    })))
{
    _renderMediator->SetSubmitRenderCommandsCallback([this](const VkCommandBuffer& commandBuffer)
    {
        SubmitRenderCommands(commandBuffer);
    });
}

// ---------------------------------------------------------------------------------------------------------------------

TriangleRenderer::~TriangleRenderer()
{
    _renderMediator->Delete();
}

// ---------------------------------------------------------------------------------------------------------------------

void TriangleRenderer::SubmitRenderCommands(const VkCommandBuffer& commandBuffer)
{
    VkBuffer buffers[] = {_vertexBuffer->GetHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer,
                           0,
                           1,
                           buffers,
                           offsets);
    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
}

// ---------------------------------------------------------------------------------------------------------------------