#include "Window.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <utility>

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(WindowSettings settings)
    : _applyNewSettings(false)
    , _settings(std::move(settings))
    , _applyNewIcon(false)
    , _icon(new sf::Image())
    , _renderWindow(new sf::RenderWindow(_settings.GetVideoMode(), 
                                         _settings.title, 
                                         _settings.GetSfmlStyle(), 
                                         _settings.GetContextSettings()))
{
    _renderWindow->setKeyRepeatEnabled(false);
    _renderWindow->setVerticalSyncEnabled(_settings.verticalSync);
    _renderWindow->setFramerateLimit(_settings.frameLimit);
    _renderWindow->setMouseCursorVisible(_settings.cursorIsVisible);
    _renderWindow->setMouseCursorGrabbed(_settings.cursorIsGrabbed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::~Window()
{
    _renderWindow->close();
    delete _renderWindow;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetSettings(WindowSettings settings)
{
    _settings = std::move(settings);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WindowSettings& Window::GetSettings() const
{
    return _settings;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetIcon(const sf::Image& icon)
{
    *_icon = icon;
    _applyNewIcon = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Window::IsOpen() const
{
    return _renderWindow->isOpen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::PollEvents(Input::InputSystemHandlerInterface& inputSystem, const Utility::Time& time) const
{
    sf::Event event{};

    while (_renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _renderWindow->close();
        }
        else
        {
            inputSystem.HandleInputEvent(event, time);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Window::BeginDraw()
{
    if (_applyNewSettings)
    {
        _ApplySettings();
    }
    else if (_applyNewIcon)
    {
        _renderWindow->setIcon(_icon->getSize().x, _icon->getSize().y, _icon->getPixelsPtr());
        _applyNewIcon = false;
    }

    _renderWindow->clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::Draw(const sf::Drawable& drawable) const
{
    _renderWindow->draw(drawable);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Renderer::Window::EndDraw() const
{
    _renderWindow->display();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::_ApplySettings()
{
    // Recreate window
    _renderWindow->create(_settings.GetVideoMode(), _settings.title, _settings.GetSfmlStyle(), _settings.GetContextSettings());

    // Set some default parameters
    _renderWindow->setKeyRepeatEnabled(false);

    // Set icon for window
    _renderWindow->setIcon(_icon->getSize().x, _icon->getSize().y, _icon->getPixelsPtr());

    // Set other settings
    _renderWindow->setVerticalSyncEnabled(_settings.verticalSync);
    _renderWindow->setFramerateLimit(_settings.frameLimit);
    _renderWindow->setMouseCursorVisible(_settings.cursorIsVisible);
    _renderWindow->setMouseCursorGrabbed(_settings.cursorIsGrabbed);

    _applyNewSettings = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
