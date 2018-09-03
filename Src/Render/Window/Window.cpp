#include "Window.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <utility>

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(WindowSettings settings)
: _settings(std::move(settings))
, _icon(new sf::Image())
, _renderWindow(std::make_unique<sf::RenderWindow>(_settings.GetVideoMode(),
                                                   _settings.title, 
                                                   _settings.GetSfmlStyle(), 
                                                   _settings.GetContextSettings()))
{
    _renderWindow->setKeyRepeatEnabled(false);
    _renderWindow->setSize({ _settings.width, _settings.height });
    _renderWindow->setVerticalSyncEnabled(_settings.verticalSync);
    _renderWindow->setFramerateLimit(_settings.frameLimit);
    _renderWindow->setMouseCursorVisible(_settings.cursorIsVisible);
    _renderWindow->setMouseCursorGrabbed(_settings.cursorIsGrabbed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::~Window()
{
    _renderWindow->close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetNewSettings(WindowSettings windowSettings)
{
    _settings = std::move(windowSettings);

    // Recreate window
    _renderWindow->create(_settings.GetVideoMode(), _settings.title, _settings.GetSfmlStyle(), _settings.GetContextSettings());

    // Set some default parameters
    _renderWindow->setKeyRepeatEnabled(false);

    // Set window size
    _renderWindow->setSize({ _settings.width, _settings.height });

    // Set other settings
    _renderWindow->setVerticalSyncEnabled(_settings.verticalSync);
    _renderWindow->setFramerateLimit(_settings.frameLimit);
    _renderWindow->setMouseCursorVisible(_settings.cursorIsVisible);
    _renderWindow->setMouseCursorGrabbed(_settings.cursorIsGrabbed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const WindowSettings& Window::GetSettings() const
{
    return _settings;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetTitle(const std::string& title)
{
    _settings.title = title;
    _renderWindow->setTitle(title);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetSize(const uint32_t width, const uint32_t height)
{
    _settings.width = width;
    _settings.height = height;
    _renderWindow->setSize({ width, height });
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetResolution(const uint32_t width, const uint32_t height)
{
    _settings.resolutionWidth = width;
    _settings.resolutionHeight = height;
    _renderWindow->create(_settings.GetVideoMode(), 
                          _settings.title, 
                          _settings.GetSfmlStyle(), 
                          _settings.GetContextSettings());
    _renderWindow->setSize({ _settings.width, _settings.height });
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetIcon(const sf::Image& icon)
{
    *_icon = icon;
    _renderWindow->setIcon(_icon->getSize().x, _icon->getSize().y, _icon->getPixelsPtr());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetAntialiasing(const uint32_t antialiasingLevel)
{
    _settings.antialiasing = antialiasingLevel;
    _renderWindow->create(_settings.GetVideoMode(), 
                          _settings.title, 
                          _settings.GetSfmlStyle(), 
                          _settings.GetContextSettings());
    _renderWindow->setSize({ _settings.width, _settings.height });
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetVerticalSyncEnabled(const bool enabled)
{
    _settings.verticalSync = enabled;
    _renderWindow->setVerticalSyncEnabled(enabled);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetFramerateLimit(const uint32_t frameLimit)
{
    _settings.frameLimit = frameLimit;
    _renderWindow->setFramerateLimit(frameLimit);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetMouseCursorVisible(const bool visible)
{
    _settings.cursorIsVisible = visible;
    _renderWindow->setMouseCursorVisible(visible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::SetMouseCursorGrabbed(const bool grabbed)
{
    _settings.cursorIsGrabbed = grabbed;
    _renderWindow->setMouseCursorGrabbed(grabbed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Window::IsOpen() const
{
    return _renderWindow->isOpen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::PollEvents(InputSystemHandlerInterface& inputSystem) const
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
            inputSystem.HandleInputEvent(event);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::BeginDraw() const
{
    _renderWindow->clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::Draw(const sf::Drawable& drawable) const
{
    _renderWindow->draw(drawable);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Window::EndDraw() const
{
    _renderWindow->display();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
