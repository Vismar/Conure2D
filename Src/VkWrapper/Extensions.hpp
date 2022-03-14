#pragma once
#include <vector>

namespace C2D::VkWrapper
{
    class Extensions final
    {
    public:
        Extensions();

        [[nodiscard]]
        const std::vector<const char*>& GetExtensions() const;

    private:
        [[nodiscard]]
        bool CheckSupport() const;

        std::vector<const char*> _requiredExtensions;
    };
}