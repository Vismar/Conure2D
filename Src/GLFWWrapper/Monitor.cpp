#include "Monitor.hpp"
#include <Utility/Assert.hpp>

using namespace C2D::GLFWWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Monitor::Monitor(GLFWmonitor* monitor)
: _monitor(monitor)
{
    Assert(_monitor != nullptr, "Provided monitor is nullptr");

    int32_t numberOfVideoModes;
    auto* videoModes = glfwGetVideoModes(_monitor, &numberOfVideoModes);
    VideoMode selectedVideoMode(*glfwGetVideoMode(_monitor));

    for (auto i = 0; i < numberOfVideoModes; ++i)
    {
        _videoModes.emplace_back(VideoMode(videoModes[i]));
        if (_videoModes.back() == selectedVideoMode)
        {
            _selectedVideoMode = static_cast<size_t>(i);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

std::string_view Monitor::GetName() const
{
    return glfwGetMonitorName(_monitor);
}

// ---------------------------------------------------------------------------------------------------------------------

const std::vector<VideoMode>& Monitor::GetVideoModes() const
{
    return _videoModes;
}

// ---------------------------------------------------------------------------------------------------------------------

void Monitor::SelectVideoMode(size_t videoModeNumber)
{
    Assert(videoModeNumber < _videoModes.size(),
           "Specified videoModeNumber is bigger or equal than the number of video modes");
    _selectedVideoMode = videoModeNumber;
}

// ---------------------------------------------------------------------------------------------------------------------

const VideoMode& Monitor::GetSelectedVideoMode() const
{
    return _videoModes[_selectedVideoMode];
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<int32_t, int32_t> Monitor::GetContentScale() const
{
    int32_t xScale, yScale;
    glfwGetMonitorPhysicalSize(_monitor, &xScale, &yScale);
    return std::tie(xScale, yScale);
}

// ---------------------------------------------------------------------------------------------------------------------

GLFWmonitor* Monitor::GetHandle() const
{
    return _monitor;
}

// ---------------------------------------------------------------------------------------------------------------------