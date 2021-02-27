#pragma once
#include <unordered_map>
#include <VkWrapper/PipelineShader.hpp>

namespace VkWrapper
{
    class ShaderManager final
    {
    public:
        [[nodiscard]]
        const PipelineShader& GetPipelineShader(const std::string& shaderName);

    private:
        std::unordered_map<std::string, PipelineShader> _pipelineShaders;
    };
}