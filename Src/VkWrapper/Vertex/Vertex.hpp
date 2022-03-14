#pragma once
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace C2D::VkWrapper
{
    class Vertex final
    {
    public:
        glm::vec2 position;
        glm::vec3 color;

        static const VkVertexInputBindingDescription& GetBindingDescription();

        static const std::array<VkVertexInputAttributeDescription, 2>& GetAttributeDescriptions();

    private:
        static VkVertexInputBindingDescription _bindingDescription;
        static std::array<VkVertexInputAttributeDescription, 2> _attributeDescriptions;
    };
}
