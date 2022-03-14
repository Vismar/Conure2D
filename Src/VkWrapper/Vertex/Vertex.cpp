#include "Vertex.hpp"

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

VkVertexInputBindingDescription Vertex::_bindingDescription =
{
    VkVertexInputBindingDescription
    {
        .binding = 0,
        .stride = sizeof(Vertex),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    }
};

std::array<VkVertexInputAttributeDescription, 2> Vertex::_attributeDescriptions =
{
    std::array<VkVertexInputAttributeDescription, 2>
    {
        VkVertexInputAttributeDescription
        {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = offsetof(Vertex, position)
        },
        VkVertexInputAttributeDescription
        {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(Vertex, color)
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

const VkVertexInputBindingDescription& Vertex::GetBindingDescription()
{
    return _bindingDescription;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::array<VkVertexInputAttributeDescription, 2>& Vertex::GetAttributeDescriptions()
{
    return _attributeDescriptions;
}

// ---------------------------------------------------------------------------------------------------------------------