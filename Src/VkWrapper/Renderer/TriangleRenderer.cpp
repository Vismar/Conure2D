#include "TriangleRenderer.hpp"

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

TriangleRenderer::TriangleRenderer(const VertexBufferArray& bufferArray)
: _bufferArray(bufferArray)
{ }

// ---------------------------------------------------------------------------------------------------------------------

void TriangleRenderer::SubmitRenderCommands(const VkCommandBuffer& commandBuffer)
{
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer,
                           0,
                           _bufferArray.GetNumberOfBuffers(),
                           _bufferArray.GetPtrToBuffers(),
                           offsets);
    vkCmdDraw(commandBuffer, _bufferArray.GetVertexCount(), 1, 0, 0);
}

// ---------------------------------------------------------------------------------------------------------------------