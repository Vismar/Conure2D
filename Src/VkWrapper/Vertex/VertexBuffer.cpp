#include "VertexBuffer.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>


#include <Logger/Logger.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer::VertexBuffer(VkDevice lDevice,
                           std::reference_wrapper<SuitablePDevice> pDevice,
                           std::vector<Vertex>&& vertices)
: _lDevice(lDevice)
, _pDevice(pDevice)
, _vertices(std::move(vertices))
{
    TraceIt;

    VkBufferCreateInfo bufferInfo
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = sizeof(_vertices[0]) * _vertices.size(),
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    Assert(vkCreateBuffer(_lDevice, &bufferInfo, nullptr, &_vertexBuffer) == VK_SUCCESS,
           "Failed to create vertex buffer");

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(_lDevice, _vertexBuffer, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits,
                                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
    };

    Assert(vkAllocateMemory(_lDevice, &allocateInfo, nullptr, &_vertexBufferMemory) == VK_SUCCESS,
           "Failed to allocate vertex buffer memory");

    vkBindBufferMemory(_lDevice, _vertexBuffer, _vertexBufferMemory, 0);

    void* data;
    vkMapMemory(_lDevice, _vertexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, _vertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(_lDevice, _vertexBufferMemory);
}

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer::~VertexBuffer()
{
    if (!_moved)
    {
        vkDestroyBuffer(_lDevice, _vertexBuffer, nullptr);
        vkFreeMemory(_lDevice, _vertexBufferMemory, nullptr);

        LOG_INFO("Vertex buffer destroyed");
    }
}

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
: _lDevice(other._lDevice)
, _pDevice(other._pDevice)
, _vertexBuffer(other._vertexBuffer)
, _vertexBufferMemory(other._vertexBufferMemory)
, _vertices(std::move(other._vertices))
{
    if (other._moved)
    {
        LOG_ERROR("This VertexBuffer was already copy-moved by someone else so it can't be used");
    }

    other._moved = true;
}

// ---------------------------------------------------------------------------------------------------------------------

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    _moved = false;
    if (other._moved)
    {
        _moved = true;
        LOG_ERROR("This VertexBuffer was already copy-moved by someone else so it can't be used");

        return * this;
    }

    _lDevice = other._lDevice;
    _pDevice = other._pDevice;
    _vertexBuffer = other._vertexBuffer;
    _vertexBufferMemory = other._vertexBufferMemory;
    _vertices = std::move(other._vertices);
    other._moved = true;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

VkBuffer VertexBuffer::GetHandle() const
{
    return _vertexBuffer;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<Vertex>& VertexBuffer::GetVertices() const
{
    return _vertices;
}

// ---------------------------------------------------------------------------------------------------------------------

uint32_t VertexBuffer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    const auto& memoryProperties = _pDevice.get().GetPDevice().GetMemoryProperties();
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if (typeFilter & (1 << i) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    Assert(false, "Failed to find suitable memory type");

    return 0;
}

// ---------------------------------------------------------------------------------------------------------------------