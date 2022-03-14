#include "Shader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Shader::Shader(Type type, std::string_view shaderName)
: _pathToShaderSrc(shaderName)
, _pathToShaderCompiled(shaderName)
{
    switch (type)
    {
        case Type::Vertex:
            _pathToShaderSrc += ".vert";
            _pathToShaderCompiled += "Vert.spv";
            break;
        case Type::Fragment:
            _pathToShaderSrc += ".frag";
            _pathToShaderCompiled += "Frag.spv";
            break;
    }

    std::filesystem::path shaderCompiled = _pathToShaderCompiled;
    if (std::filesystem::exists(shaderCompiled))
    {
        Load();
        return;
    }

    std::filesystem::path shaderSrc = _pathToShaderSrc;
    std::string errorMessage = "Specified shader (";
    errorMessage.append(_pathToShaderSrc);
    errorMessage.append(") does not exist");
    Assert(std::filesystem::exists(shaderSrc), errorMessage.c_str());

    Compile();
    Load();
}

// ---------------------------------------------------------------------------------------------------------------------

VkShaderModule Shader::CreateModule(VkDevice lDevice) const
{
    VkShaderModuleCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = _byteCode.size(),
        .pCode = reinterpret_cast<const uint32_t*>(_byteCode.data())
    };
    VkShaderModule shaderModule;
    Assert(vkCreateShaderModule(lDevice, &createInfo, nullptr, &shaderModule) == VK_SUCCESS, "");
    return shaderModule;
}

// ---------------------------------------------------------------------------------------------------------------------

void Shader::Compile()
{
    TraceIt;

    std::stringstream stringStream;
    stringStream << "glslc.exe " << _pathToShaderSrc<< " -o " << _pathToShaderCompiled;
    std::system(stringStream.str().c_str());
}

// ---------------------------------------------------------------------------------------------------------------------

void Shader::Load()
{
    TraceIt;

    std::ifstream file(_pathToShaderCompiled.c_str(), std::ios::ate | std::ios::binary);
    size_t fileSize = static_cast<size_t>(file.tellg());
    _byteCode.resize(fileSize);
    file.seekg(0);
    file.read(_byteCode.data(), fileSize);

    file.close();
}

// ---------------------------------------------------------------------------------------------------------------------