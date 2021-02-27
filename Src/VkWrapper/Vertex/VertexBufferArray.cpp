#include "VertexBufferArray.hpp"

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

VertexBufferArray::VertexBufferArray(std::vector<VertexBuffer>&& vertexBuffers)
: _vertexBuffers(std::move(vertexBuffers))
{
    for (const auto& vertexBuffer : _vertexBuffers)
    {
        _vkBuffers.push_back(vertexBuffer.GetHandle());
        _vertexCount += vertexBuffer.GetVertices().size();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

uint32_t VertexBufferArray::GetNumberOfBuffers() const
{
    return _vkBuffers.size();
}

// ---------------------------------------------------------------------------------------------------------------------

uint32_t VertexBufferArray::GetVertexCount() const
{
    return _vertexCount;
}

// ---------------------------------------------------------------------------------------------------------------------

const VkBuffer* VertexBufferArray::GetPtrToBuffers() const
{
    return _vkBuffers.data();
}

// ---------------------------------------------------------------------------------------------------------------------