#include "PipelineShader.hpp"
#include <VkWrapper/Renderer/RenderMediator.hpp>

using namespace C2D::VkWrapper;

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
: _shaderName(shaderName)
, _vertexShader(Shader(Shader::Type::Vertex, shaderName))
, _fragmentShader(Shader(Shader::Type::Fragment, shaderName))
{ }

// ---------------------------------------------------------------------------------------------------------------------

const std::string& PipelineShader::Name() const
{
    return _shaderName;
}

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

RenderMediatorHandle PipelineShader::AddRenderMediator(const std::shared_ptr<RenderMediator>& renderer)
{
    _renderMediators.push_back(renderer);
    return std::prev(_renderMediators.end());
}

// ---------------------------------------------------------------------------------------------------------------------

void PipelineShader::RemoveRenderMediator(const RenderMediatorHandle& handle)
{
    _renderMediators.erase(handle);
}

// ---------------------------------------------------------------------------------------------------------------------


void PipelineShader::RemoveAllRenderMediators()
{
    _renderMediators.clear();
}

// ---------------------------------------------------------------------------------------------------------------------

void PipelineShader::SubmitUserCommands(const VkCommandBuffer& commandBuffer) const
{
    for (const auto& user : _renderMediators)
    {
        user->SubmitRenderCommands(commandBuffer);
    }
}

// ---------------------------------------------------------------------------------------------------------------------