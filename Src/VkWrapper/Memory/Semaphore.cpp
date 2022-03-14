#include "Semaphore.hpp"
#include <Utility/Assert.hpp>
#include <Tracer/TraceScopeTimer.hpp>

using namespace C2D::VkWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Semaphore::Semaphore(VkDevice lDevice)
: _lDevice(lDevice)
, _semaphore(nullptr)
{
    TraceIt;

    VkSemaphoreCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    };

    Assert(vkCreateSemaphore(_lDevice, &createInfo, nullptr, &_semaphore) == VK_SUCCESS,
           "Failed to create semaphore");
}

// ---------------------------------------------------------------------------------------------------------------------

Semaphore::~Semaphore()
{
    vkDestroySemaphore(_lDevice, _semaphore, nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

VkSemaphore Semaphore::GetHandle() const
{
    return _semaphore;
}

// ---------------------------------------------------------------------------------------------------------------------