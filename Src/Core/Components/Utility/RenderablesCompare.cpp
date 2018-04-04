#include "Core/Components/RenderableComponent.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderablesCompare::operator() (const std::shared_ptr<RenderableComponent>& first,
                                    const std::shared_ptr<RenderableComponent>& second) const
{
    return *first < *second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderablesCompare::operator()(const std::shared_ptr<RenderableComponent>& first, 
                                   const RenderableComponent& second) const
{
    return *first < second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderablesCompare::operator()(const RenderableComponent& first, 
                                   const std::shared_ptr<RenderableComponent>& second) const
{
    return first < *second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderablesCompare::operator()(const std::weak_ptr<RenderableComponent>& first, 
                                   const std::weak_ptr<RenderableComponent>& second) const
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

bool RenderablesCompare::operator()(const std::weak_ptr<RenderableComponent>& first, 
                                   const RenderableComponent& second) const
{
    bool less(true);

    if (const auto lockedFirst = first.lock())
    {
        less = *lockedFirst < second;
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RenderablesCompare::operator()(const RenderableComponent& first, 
                                   const std::weak_ptr<RenderableComponent>& second) const
{
    bool less(true);

    if (const auto lockedSecond = second.lock())
    {
        less = first < *lockedSecond;
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
