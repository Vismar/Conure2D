#include "CamerasCompare.hpp"
#include "Core/Components/CameraComponent.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator() (const std::shared_ptr<CameraComponent>& first,
                                 const std::shared_ptr<CameraComponent>& second) const
{
    return *first < *second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator()(const std::shared_ptr<CameraComponent>& first,
                                const CameraComponent& second) const
{
    return *first < second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator()(const CameraComponent& first,
                                const std::shared_ptr<CameraComponent>& second) const
{
    return first < *second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator()(const std::weak_ptr<CameraComponent>& first,
                                const std::weak_ptr<CameraComponent>& second) const
{
    bool less(true);

    if (const auto lockedFirst = first.lock())
    {
        if (const auto lockedSecond = second.lock())
        {
            less = *lockedFirst < *lockedSecond;
        }
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator()(const std::weak_ptr<CameraComponent>& first,
                                const CameraComponent& second) const
{
    bool less(true);

    if (const auto lockedFirst = first.lock())
    {
        less = *lockedFirst < second;
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CamerasCompare::operator()(const CameraComponent& first,
                                const std::weak_ptr<CameraComponent>& second) const
{
    bool less(true);

    if (const auto lockedSecond = second.lock())
    {
        less = first < *lockedSecond;
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
