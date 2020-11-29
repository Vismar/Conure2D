#pragma once
#include <VkWrapper/Context.hpp>
#include <GLFWWrapper/Window.hpp>

namespace VkWrapper
{
    class Surface final
    {
    public:
        Surface(const Context& context, const GLFWWrapper::Window& window);
        ~Surface();

        [[nodiscard]]
        VkSurfaceKHR GetHandle() const;

    private:
        const Context& _context;
        VkSurfaceKHR _surface{};
    };
}