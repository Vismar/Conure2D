#include "CameraComponent.hpp"
#include "Core/Components/TransformComponent.hpp"
#include "Core/Scene/SceneObject.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraComponent::CameraComponent(std::weak_ptr<SceneObject> &&sceneObject)
: BaseDataComponent(std::move(sceneObject))
, _priority(0)
, _size(640.0f, 480.0f)
, _viewportLeftCoord(0.0f)
, _viewportTopCoord(0.0f)
, _viewportWidth(1.0f)
, _viewportHeight(1.0f)
{
    if (const auto object = GetSceneObject().lock())
    {
        _transformComponent = object->GetTransformComponent();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CameraComponent::operator<(const CameraComponent& right) const
{
    bool less(true);

    // If priority numbers are the same, then we can just compare ids of scene objects that owns this components
    if (_priority == right._priority)
    {
        if (const auto leftObject = GetSceneObject().lock())
        {
            if (const auto rightObject = right.GetSceneObject().lock())
            {
                less = leftObject->GetId() < rightObject->GetId();
            }
        }
    }
    // If layer numbers are different, then just compare them
    else
    {
        less = _priority < right._priority;
    }

    return less;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CameraComponent::operator>(const CameraComponent& right) const
{
    return (right < (*this));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CameraComponent::operator<=(const CameraComponent& right) const
{
    return !((*this) > right);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CameraComponent::operator>=(const CameraComponent& right) const
{
    return !(right < (*this));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraComponent::operator sf::View() const
{
    sf::View view;
    if (auto transform = _transformComponent.lock())
    {
        const auto pos(transform->GetGlobalPosition());
        const Vector2f size(_size);
        const auto x(pos.x + size.x / 2.0f);
        const auto y(pos.y + size.y / 2.0f);
        view.setCenter(x, y);
        view.setSize(size.x, size.y);
        view.setRotation(transform->GetGlobalRotation());
        view.setViewport({ _viewportLeftCoord.load(), _viewportTopCoord.load(),
                           _viewportWidth.load(), _viewportHeight.load() });
    }

    return view;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraComponent::SetPriority(uint8_t newPriority)
{
    if (_priority.load() != newPriority)
    {
        _priority = newPriority;

        const auto thisComponent = std::dynamic_pointer_cast<CameraComponent>(this->shared_from_this());
        //InvokeEvent<void, std::weak_ptr<CameraComponent>, const int8_t>("PriorityUpdated", thisComponent, _priority.load());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t CameraComponent::GetPriority() const
{
    return _priority.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraComponent::SetSize(const Vector2f& newSize)
{
    _size = newSize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2f CameraComponent::GetSize() const
{
    return Vector2f(_size);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraComponent::SetViewport(const sf::FloatRect& newViewport)
{
    _viewportLeftCoord = newViewport.left;
    _viewportTopCoord = newViewport.top;
    _viewportWidth = newViewport.width;
    _viewportHeight = newViewport.height;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::FloatRect CameraComponent::GetViewport() const
{
    return { _viewportLeftCoord.load(), _viewportTopCoord.load(), _viewportWidth.load(), _viewportHeight.load() };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraComponent::Initialize()
{
    _typeIndex = typeid(CameraComponent);

    //AddEvent("PriorityUpdated", new Dispatcher<void>());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
