#include "VideoMode.hpp"
#include <sstream>

using namespace GLFWWrapper;

// ---------------------------------------------------------------------------------------------------------------------

VideoMode::VideoMode(const GLFWvidmode& videoMode)
: _videoMode(videoMode)
{ }

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetWidth() const
{
    return _videoMode.width;
}

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetHeight() const
{
    return _videoMode.height;
}

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetRedBits() const
{
    return _videoMode.redBits;
}

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetGreenBits() const
{
    return _videoMode.greenBits;
}

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetBlueBits() const
{
    return _videoMode.blueBits;
}

// ---------------------------------------------------------------------------------------------------------------------

int32_t VideoMode::GetRefreshRate() const
{
    return _videoMode.refreshRate;
}

// ---------------------------------------------------------------------------------------------------------------------

std::string VideoMode::AsString() const
{
    std::stringstream stringStream;
    stringStream << "Res: " << GetWidth() << 'x' << GetHeight()
                 << "; Bits: R(" << GetRedBits() << ")G(" << GetGreenBits() << ")B(" << GetBlueBits()
                 << "); RefreshRate: " << GetRefreshRate() << ';';

    return stringStream.str();
}

// ---------------------------------------------------------------------------------------------------------------------

bool VideoMode::operator==(const VideoMode& right) const
{
    return _videoMode.width == right.GetWidth() &&
           _videoMode.height == right.GetHeight() &&
           _videoMode.redBits == right.GetRedBits() &&
           _videoMode.greenBits == right.GetGreenBits() &&
           _videoMode.blueBits == right.GetBlueBits() &&
           _videoMode.refreshRate == right.GetRefreshRate();
}

// ---------------------------------------------------------------------------------------------------------------------