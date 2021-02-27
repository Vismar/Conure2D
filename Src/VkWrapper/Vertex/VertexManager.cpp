#include "VertexManager.hpp"

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

VertexManager::VertexManager(VkDevice lDevice, std::reference_wrapper<SuitablePDevice> pDevice)
: _lDevice(lDevice)
, _pDevice(pDevice)
{
    std::vector<VertexBuffer> defaultVertexBuffers;
    defaultVertexBuffers.emplace_back(
        VertexBuffer
        {
            _lDevice,
            _pDevice,
            {
                Vertex
                {
                    .position{0.0f, -0.5f},
                    .color{1.0f, 0.0f, 0.0f}
                },
                Vertex
                {
                    .position{0.5f, 0.5f},
                    .color{0.0f, 1.0f, 0.0f}
                },
                Vertex
                {
                    .position{-0.5f, 0.5f},
                    .color{0.0f, 0.0f, 1.0f}
                }
            }
        });
    auto [position, added] = _vertexBuffers.emplace("default", std::move(defaultVertexBuffers));

    _defaultVertexBuffer = position;
}

// ---------------------------------------------------------------------------------------------------------------------

const VertexBufferArray& VertexManager::GetVertexBuffers(const std::string& shaderName)
{
    auto position = _vertexBuffers.find(shaderName);
    if (position == _vertexBuffers.end())
    {
        position = _defaultVertexBuffer;
    }

    return position->second;
}

// ---------------------------------------------------------------------------------------------------------------------