#include "Fence.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Fence::Fence(VkDevice lDevice)
: _lDevice(lDevice)
, _fence(nullptr)
{
    TraceIt;

    VkFenceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    Assert(vkCreateFence(_lDevice, &createInfo, nullptr, &_fence) == VK_SUCCESS,
           "Failed to create fence");
}

// ---------------------------------------------------------------------------------------------------------------------

Fence::~Fence()
{
    vkDestroyFence(_lDevice, _fence, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

const VkFence& Fence::GetHandle() const
{
    return _fence;
}

// ---------------------------------------------------------------------------------------------------------------------