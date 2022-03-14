#include "CommandPool.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

CommandPool::CommandPool(VkDevice lDevice, uint32_t graphicsFamilyIndex)
: _lDevice(lDevice)
, _commandPool(nullptr)
{
    TraceIt;

    VkCommandPoolCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = graphicsFamilyIndex
    };

    Assert(vkCreateCommandPool(_lDevice, &createInfo, nullptr, &_commandPool) == VK_SUCCESS,
           "Failed to create command pool");
}

// ---------------------------------------------------------------------------------------------------------------------

CommandPool::~CommandPool()
{
    vkDestroyCommandPool(_lDevice, _commandPool, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

void CommandPool::Reset()
{
    vkResetCommandPool(_lDevice, _commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}

// ---------------------------------------------------------------------------------------------------------------------

VkCommandPool CommandPool::GetHandle() const
{
    return _commandPool;
}

// ---------------------------------------------------------------------------------------------------------------------