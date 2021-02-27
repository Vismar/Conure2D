#pragma once
#include <VkWrapper/Shader/Shader.hpp>

namespace VkWrapper
{
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
        PipelineShaderCreationInfo GetVertexShaderCreationInfo(VkDevice lDevice) const;

        [[nodiscard]]
        PipelineShaderCreationInfo GetFragmentShaderCreationInfo(VkDevice lDevice) const;

    private:
        Shader _vertexShader;
        Shader _fragmentShader;
    };
}