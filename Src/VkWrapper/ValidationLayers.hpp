#pragma once
#include <vector>

namespace VkWrapper
{
    class ValidationLayers final
    {
    public:
        ValidationLayers();

        [[nodiscard]]
        const std::vector<const char*>& GetLayers() const;

    private:
        [[nodiscard]]
        bool CheckSupport() const;

        const std::vector<const char*> _validationLayers;
    };
}