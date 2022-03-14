#include "Context.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Utility/Assert.hpp>
#include <Logger/Logger.hpp>

using namespace C2D::GLFWWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Context::Context()
{
    Assert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");
    LOG_INFO("GLFW context was initialized");
}

// ---------------------------------------------------------------------------------------------------------------------

Context::~Context()
{
    glfwTerminate();
    LOG_INFO("GLFW context was terminated");
}

// ---------------------------------------------------------------------------------------------------------------------