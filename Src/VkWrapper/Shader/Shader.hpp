#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace VkWrapper
{
    class Shader final
    {
    public:
        enum class Type
        {
            Vertex,
            Fragment
        };

        explicit Shader(Type type, std::string_view shaderName);

        [[nodiscard]]
        VkShaderModule CreateModule(VkDevice lDevice) const;

    private:
        void Compile();
        void Load();

        std::string _pathToShaderSrc;
        std::string _pathToShaderCompiled;
        std::vector<char> _byteCode;
    };
}