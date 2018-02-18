#include "WindowSettings.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "SFML/Window/ContextSettings.hpp"

using namespace Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::VideoMode WindowSettings::GetVideoMode() const
{
    return { width, height, bitsPerPixel };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int WindowSettings::GetSfmlStyle() const
{
    unsigned int sfStyle = sf::Style::Close;

    switch (style)
    {
    case WindowStyle::FullScreen:
        sfStyle =  sf::Style::Fullscreen;
        break;
    case WindowStyle::Windowed:
        sfStyle = sf::Style::Close;
        break;
    case WindowStyle::NoBorders:
        sfStyle = sf::Style::None;
        break;
    }

    return sfStyle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::ContextSettings WindowSettings::GetContextSettings() const
{
    return sf::ContextSettings(depthBits, stencilBits, antialiasing, majorContextVersion, minorContaxtVersion);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
