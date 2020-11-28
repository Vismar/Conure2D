#include "Context.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Utility/Assert.hpp>
#include <Logger/Logger.hpp>

using namespace GLFWWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Context::Context()
{
    Assert(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");
    Logger::LogInfo("GLFW context was initialized", __PRETTY_FUNCTION__);
}

// ---------------------------------------------------------------------------------------------------------------------

Context::~Context()
{
    glfwTerminate();
    Logger::LogInfo("GLFW context was terminated", __PRETTY_FUNCTION__);
}

// ---------------------------------------------------------------------------------------------------------------------