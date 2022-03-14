#pragma once
#include <memory>
#include <list>
#include <VkWrapper/Shader/Shader.hpp>

namespace C2D::VkWrapper
{
    class RenderMediator;
    using RenderMediatorHandle = std::list<std::shared_ptr<RenderMediator>>::iterator;

    class PipelineShader final
    {
    public:
        struct PipelineShaderCreationInfo
        {
            explicit PipelineShaderCreationInfo(VkDevice lDevice);
            ~PipelineShaderCreationInfo();

            VkShaderModule module{};
            VkPipelineShaderStageCreateInfo createInfo{};

        private:
            VkDevice _lDevice;
        };

    public:
        explicit PipelineShader(std::string_view shaderName);

        [[nodiscard]]
        const std::string& Name() const;

        [[nodiscard]]
        PipelineShaderCreationInfo GetVertexShaderCreationInfo(VkDevice lDevice) const;

        [[nodiscard]]
        PipelineShaderCreationInfo GetFragmentShaderCreationInfo(VkDevice lDevice) const;

        RenderMediatorHandle AddRenderMediator(const std::shared_ptr<RenderMediator>& renderer);
        void RemoveRenderMediator(const RenderMediatorHandle& handle);
        void RemoveAllRenderMediators();

        void SubmitUserCommands(const VkCommandBuffer& commandBuffer) const;

    private:
        std::string _shaderName;
        Shader _vertexShader;
        Shader _fragmentShader;

        std::list<std::shared_ptr<RenderMediator>> _renderMediators;
    };
}