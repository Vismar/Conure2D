#pragma once
#include <memory>
#include <vulkan/vulkan.h>

namespace C2D
{
    namespace VkWrapper
    {
        class IRenderMediator;
        class VertexBuffer;
    }

    // TODO: Instead of triangle renderer there should be a generic base renderer which we can inherit from.
    //       This class currently is just an example. Later we need to introduce binding of an actual vertex buffer.

    class TriangleRenderer final
    {
    public:
        explicit TriangleRenderer(std::shared_ptr<VkWrapper::IRenderMediator>&& renderMediator);
        ~TriangleRenderer();

    private:
        void SubmitRenderCommands(const VkCommandBuffer& commandBuffer);

        std::shared_ptr<VkWrapper::IRenderMediator> _renderMediator;
        std::unique_ptr<VkWrapper::VertexBuffer> _vertexBuffer;
    };
}