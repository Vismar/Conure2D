#pragma once
#include <VkWrapper/Renderer/BaseRenderer.hpp>
#include <VkWrapper/Vertex/VertexBufferArray.hpp>

namespace C2D::VkWrapper
{
    class TriangleRenderer final : public BaseRenderer
    {
    public:
        explicit TriangleRenderer(const VertexBufferArray& bufferArray);

        void SubmitRenderCommands(const VkCommandBuffer& commandBuffer) override;

    private:
        const VertexBufferArray& _bufferArray;
    };
}