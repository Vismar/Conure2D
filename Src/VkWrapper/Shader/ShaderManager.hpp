#pragma once
#include <unordered_map>
#include <VkWrapper/Shader/PipelineShader.hpp>

namespace C2D::VkWrapper
{
    class ShaderManager final
    {
    public:
        void AddShader(const std::string& shaderName);
        [[nodiscard]]
        PipelineShader& GetPipelineShader(const std::string& shaderName);
        const std::vector<std::string>& GetShaderNames() const;

    private:
        std::unordered_map<std::string, PipelineShader> _pipelineShaders;
        std::vector<std::string> _shaderNames;
    };
}