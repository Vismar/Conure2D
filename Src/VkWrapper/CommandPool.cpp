#include "CommandPool.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

CommandPool::CommandPool(VkDevice lDevice, uint32_t graphicsFamilyIndex)
: _lDevice(lDevice)
, _commandPool(nullptr)
{
    TraceIt;

    VkCommandPoolCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = 0,
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

VkCommandPool CommandPool::GetHandle() const
{
    return _commandPool;
}

// ---------------------------------------------------------------------------------------------------------------------