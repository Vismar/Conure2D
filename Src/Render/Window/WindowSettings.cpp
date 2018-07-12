#include "WindowSettings.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/ContextSettings.hpp>

using namespace Render;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::VideoMode WindowSettings::GetVideoMode() const
{
    return { resolutionWidth, resolutionHeight, bitsPerPixel };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t WindowSettings::GetSfmlStyle() const
{
    uint32_t sfStyle = sf::Style::Close;

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
