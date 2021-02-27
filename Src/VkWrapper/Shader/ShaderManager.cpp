#include "ShaderManager.hpp"

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

const PipelineShader& ShaderManager::GetPipelineShader(const std::string& shaderName)
{
    auto position = _pipelineShaders.find(shaderName);
    if (position == _pipelineShaders.end())
    {
        auto [shaderIter, added] = _pipelineShaders.emplace(shaderName, PipelineShader(shaderName));
        return shaderIter->second;
    }

    return position->second;
}

// ---------------------------------------------------------------------------------------------------------------------