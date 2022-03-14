#pragma once
#include <VkWrapper/Vertex/VertexBuffer.hpp>

namespace C2D::VkWrapper
{
    class VertexBufferArray final
    {
    public:
        explicit VertexBufferArray(std::vector<VertexBuffer>&& vertexBuffers);

        [[nodiscard]]
        uint32_t GetNumberOfBuffers() const;

        [[nodiscard]]
        uint32_t GetVertexCount() const;

        [[nodiscard]]
        const VkBuffer* GetPtrToBuffers() const;

    private:
        uint32_t _vertexCount = 0;
        std::vector<VkBuffer> _vkBuffers;
        std::vector<VertexBuffer> _vertexBuffers;
    };
}