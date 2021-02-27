#pragma once
#include <string>
#include <unordered_map>
#include <VkWrapper/Vertex/VertexBufferArray.hpp>

namespace VkWrapper
{
    class VertexManager final
    {
    public:
        VertexManager(VkDevice lDevice, std::reference_wrapper<SuitablePDevice> pDevice);

        [[nodiscard]]
        const VertexBufferArray& GetVertexBuffers(const std::string& shaderName);

    private:
        VkDevice _lDevice;
        std::reference_wrapper<SuitablePDevice> _pDevice;
        std::unordered_map<std::string, VertexBufferArray> _vertexBuffers;
        std::unordered_map<std::string, VertexBufferArray>::iterator _defaultVertexBuffer;
    };
}