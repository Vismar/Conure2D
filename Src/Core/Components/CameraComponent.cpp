#include "CameraComponent.hpp"
#include "Core/Components/TransformComponent.hpp"
#include "Core/Scene/SceneObject.hpp"

using namespace Core;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraComponent::CameraComponent(std::weak_ptr<SceneObject> &&sceneObject)
: BaseDataComponent(std::move(sceneObject))
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

CameraComponent::operator sf::View() const
{
    sf::View view;
    if (auto transform = _transformComponent.lock())
    {
        const auto pos = transform->GetGlobalPosition();
        const Utility::Vector2F size(_size);
        const auto x = pos.x + size.x / 2.0f;
        const auto y = pos.y + size.y / 2.0f;
        view.setCenter(x, y);
        view.setSize(size.x, size.y);
        view.setRotation(transform->GetGlobalRotation());
        view.setViewport({ _viewportLeftCoord.load(), _viewportTopCoord.load(),
                           _viewportWidth.load(), _viewportHeight.load() });
    }

    return view;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraComponent::SetSize(const Utility::Vector2F& newSize)
{
    _size = newSize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Utility::Vector2F CameraComponent::GetSize() const
{
    return _size;
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
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
