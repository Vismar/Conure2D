#include "Surface.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Surface::Surface(const Context& context, const GLFWWrapper::Window& window)
: _context(context)
{
    TraceIt;

    Assert(glfwCreateWindowSurface(context.GetHandle(), window.GetHandle(), nullptr, &_surface) == VK_SUCCESS,
           "Failed to create window surface");
}

// ---------------------------------------------------------------------------------------------------------------------

Surface::~Surface()
{
    vkDestroySurfaceKHR(_context.GetHandle(), _surface, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkSurfaceKHR Surface::GetHandle() const
{
    return _surface;
}

// ---------------------------------------------------------------------------------------------------------------------