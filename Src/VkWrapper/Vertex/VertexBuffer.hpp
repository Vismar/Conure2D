#pragma once
#include <vulkan/vulkan.h>
#include <VkWrapper/SuitablePDevice.hpp>
#include <VkWrapper/Vertex/Vertex.hpp>
#include <vector>

namespace C2D::VkWrapper
{
    class VertexBuffer final
    {
    public:
        VertexBuffer(VkDevice lDevice,
                     std::reference_wrapper<SuitablePDevice> pDevice,
                     std::vector<Vertex>&& vertices);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        [[nodiscard]]
        VkBuffer GetHandle() const;

        [[nodiscard]]
        const std::vector<Vertex>& GetVertices() const;

    private:
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        bool _moved = false;
        VkDevice _lDevice;
        std::reference_wrapper<SuitablePDevice> _pDevice;
        VkBuffer _vertexBuffer{};
        VkDeviceMemory _vertexBufferMemory{};
        std::vector<Vertex> _vertices;
    };
}