#include "PipelineShader.hpp"

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader::PipelineShaderCreationInfo::PipelineShaderCreationInfo(VkDevice lDevice)
: _lDevice(lDevice)
{ }

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader::PipelineShaderCreationInfo::~PipelineShaderCreationInfo()
{
    vkDestroyShaderModule(_lDevice, module, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader::PipelineShader(std::string_view shaderName)
: _vertexShader(Shader(Shader::Type::Vertex, shaderName))
, _fragmentShader(Shader(Shader::Type::Fragment, shaderName))
{ }

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader::PipelineShaderCreationInfo PipelineShader::GetVertexShaderCreationInfo(VkDevice lDevice) const
{
    PipelineShaderCreationInfo creationInfo(lDevice);
    creationInfo.module = _vertexShader.CreateModule(lDevice);
    creationInfo.createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = creationInfo.module,
        .pName = "main"
    };

    return creationInfo;
}

// ---------------------------------------------------------------------------------------------------------------------

PipelineShader::PipelineShaderCreationInfo PipelineShader::GetFragmentShaderCreationInfo(VkDevice lDevice) const
{
    PipelineShaderCreationInfo creationInfo(lDevice);
    creationInfo.module = _fragmentShader.CreateModule(lDevice);
    creationInfo.createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = creationInfo.module,
        .pName = "main"
    };

    return creationInfo;
}

// ---------------------------------------------------------------------------------------------------------------------