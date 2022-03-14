#include "ShaderManager.hpp"

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

void ShaderManager::AddShader(const std::string& shaderName)
{
    auto position = _pipelineShaders.find(shaderName);
    if (position == _pipelineShaders.end())
    {
        _pipelineShaders.emplace(shaderName, PipelineShader(shaderName));
        _shaderNames.push_back(shaderName);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader& ShaderManager::GetPipelineShader(const std::string& shaderName)
{
    auto position = _pipelineShaders.find(shaderName);
    if (position == _pipelineShaders.end())
    {
        auto [shaderIter, added] = _pipelineShaders.emplace(shaderName, PipelineShader(shaderName));
        _shaderNames.push_back(shaderName);

        return shaderIter->second;
    }

    return position->second;
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<std::string>& ShaderManager::GetShaderNames() const
{
    return _shaderNames;
}

// ---------------------------------------------------------------------------------------------------------------------