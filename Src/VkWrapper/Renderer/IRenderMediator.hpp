#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <vulkan/vulkan.h>

namespace C2D::VkWrapper
{
    class Vertex;
    class VertexBuffer;

    using SubmitRenderCommandsCallback = std::function<void(const VkCommandBuffer& commandBuffer)>;

    class IRenderMediator
    {
    public:
        virtual void SetSubmitRenderCommandsCallback(SubmitRenderCommandsCallback&& submitRenderCommandsCallback) = 0;
        virtual void Delete() = 0;
        virtual VertexBuffer CreateVertexBuffer(std::vector<Vertex>&& vertices) = 0;
    };
}