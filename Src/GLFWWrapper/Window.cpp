#include "Window.hpp"
#include <Utility/Assert.hpp>
#include <Logger/Logger.hpp>
#include <GLFWWrapper/Monitor.hpp>

using namespace C2D::GLFWWrapper;

// ---------------------------------------------------------------------------------------------------------------------

Window::~Window()
{
    Destroy();
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Create(int width, int height, std::string_view title)
{
    Assert(_window == nullptr, "This window was already created")

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, _resizable);
    glfwWindowHint(GLFW_DECORATED, _decorated);
    _window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    Assert(_window != nullptr, "Windows was not created");
    _state = State::Normal;
    LOG_INFO("Window was created");

    // Set OnSizeChanged callback
    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, OnFramebufferResizeCallback);

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

void Window::Destroy()
{
    if (_window == nullptr)
    {
        LOG_WRN("This window is not existent so it can't be destroyed");
        return;
    }

    glfwDestroyWindow(_window);
    _window = nullptr;
    LOG_INFO("Window was destroyed");
}

// ---------------------------------------------------------------------------------------------------------------------

bool Window::IsNotClosed() const
{
    return _window != nullptr && !static_cast<bool>(glfwWindowShouldClose(_window));
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetTitle(std::string_view title)
{
    Assert(_window != nullptr, "This window is not created");

    glfwSetWindowTitle(_window, title.data());
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Window::IsResizable() const
{
    return _resizable == GLFW_TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetResizable(bool resizable)
{
    Assert(_window == nullptr, "The window is created and you can't change 'resizable' property without recreating the window.");

    _resizable = resizable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Window::IsDecorated() const
{
    return _decorated == GLFW_TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------

Window & Window::SetDecorated(bool decorated)
{
    Assert(_window == nullptr, "The window is created and you can't change 'decorated' property without recreating the window.");

    _decorated = decorated ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<int32_t, int32_t> Window::GetSize() const
{
    Assert(_window != nullptr, "This window is not created");

    int32_t width, height;
    glfwGetWindowSize(_window, &width, &height);
    return std::tie(width, height);
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetSize(int32_t width, int32_t height)
{
    Assert(_window != nullptr, "This window is not created")

    glfwSetWindowSize(_window, width, height);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetSizeLimits(int32_t mindWidth, int32_t minHeight, int32_t maxWidth, int32_t maxHeight)
{
    Assert(_window != nullptr, "This window is not created");

    glfwSetWindowSizeLimits(_window, mindWidth, minHeight, maxWidth, maxHeight);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetAspectRatio(int32_t numer, int32_t denom)
{
    Assert(_window != nullptr, "This window is not created");

    glfwSetWindowAspectRatio(_window, numer, denom);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<int32_t, int32_t> Window::GetPosition() const
{
    Assert(_window != nullptr, "This window is not created");

    int32_t xPos, yPos;
    glfwGetWindowPos(_window, &xPos, &yPos);
    return std::tie(xPos, yPos);
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetPosition(int32_t xPos, int32_t yPos)
{
    Assert(_window != nullptr, "This window is not created");

    glfwSetWindowPos(_window, xPos, yPos);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

float Window::GetOpacity() const
{
    Assert(_window != nullptr, "This window is not created");

    return glfwGetWindowOpacity(_window);
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetOpacity(float opacity)
{
    Assert(_window != nullptr, "This window is not created");

    glfwSetWindowOpacity(_window, opacity);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<int32_t, int32_t> Window::GetFrameBufferSize() const
{
    Assert(_window != nullptr, "This window is not created");

    int32_t width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    return std::tie(width, height);
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<float, float> Window::GetContentScale() const
{
    Assert(_window != nullptr, "This window is not created");

    float xScale, yScale;
    glfwGetWindowContentScale(_window, &xScale, &yScale);
    return std::tie(xScale, yScale);
}

// ---------------------------------------------------------------------------------------------------------------------

std::tuple<int32_t, int32_t, int32_t, int32_t> Window::GetFrameCoordinates() const
{
    Assert(_window != nullptr, "This window is not created");

    int32_t left, top, right, bottom;
    glfwGetWindowFrameSize(_window, &left, &top, &right, &bottom);
    return std::tie(left, top, right, bottom);
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::RequestAttention()
{
    Assert(_window != nullptr, "This window is not created");

    glfwRequestWindowAttention(_window);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Minimize()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Fullscreen)
    {
        LOG_WRN("This window is fullscreen, can't minimize it");
        return *this;
    }

    glfwIconifyWindow(_window);
    _state = State::Minimized;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Restore()
{
    Assert(_window != nullptr, "This window is not created");

    glfwRestoreWindow(_window);
    _state = State::Normal;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Maximize()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Fullscreen)
    {
        LOG_WRN("This window is fullscreen, can't maximize it");
        return *this;
    }

    glfwMaximizeWindow(_window);
    _state = State::Maximized;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Hide()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Fullscreen)
    {
        LOG_WRN("This window is fullscreen, can't hide it");
        return *this;
    }

    glfwHideWindow(_window);
    _state = State::Hidden;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Show()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Hidden)
    {
        glfwShowWindow(_window);
        if (glfwGetWindowAttrib(_window, GLFW_ICONIFIED) == GLFW_TRUE)
        {
            _state = State::Minimized;
        }
        else if (glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) == GLFW_TRUE)
        {
            _state = State::Maximized;
        }
        else
        {
            _state = State::Normal;
        }

        return *this;
    }

    LOG_WRN("This window is not hidden so there is no reason to even try to show it");
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::Focus()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Hidden || _state == State::Minimized)
    {
        LOG_WRN("This window is hidden/minimized so it can't be focused");
        return *this;
    }

    glfwFocusWindow(_window);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Window::IsFocused() const
{
    Assert(_window != nullptr, "This window is not created");

    return glfwGetWindowAttrib(_window, GLFW_FOCUSED) == GLFW_TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetFullScreenOnMonitor(const Monitor& monitor)
{
    Assert(_window != nullptr, "This window is not created");

    const auto& mode = monitor.GetSelectedVideoMode();
    glfwSetWindowMonitor(_window, monitor.GetHandle(), 0, 0, mode.GetWidth(), mode.GetHeight(), mode.GetRefreshRate());
    _state = State::Fullscreen;

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetWindowed()
{
    Assert(_window != nullptr, "This window is not created");

    if (_state == State::Fullscreen || _state == State::Borderless)
    {
        glfwSetWindowMonitor(_window, nullptr, 1280, 720, 800, 600, 0);
        _state = State::Normal;
        return *this;
    }

    LOG_WRN("This window is not fullscreen or borderless windowed so it is already windowed");
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window& Window::SetBorderlessWindowedOnMonitor(const Monitor& monitor)
{
    if (_window)
    {
        Destroy();
    }

    const auto& mode = monitor.GetSelectedVideoMode();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RED_BITS, mode.GetRedBits());
    glfwWindowHint(GLFW_GREEN_BITS, mode.GetGreenBits());
    glfwWindowHint(GLFW_BLUE_BITS, mode.GetBlueBits());
    glfwWindowHint(GLFW_REFRESH_RATE, mode.GetRefreshRate());

    _window = glfwCreateWindow(mode.GetWidth(), mode.GetHeight(), "", monitor.GetHandle(), nullptr);
    _state = State::Borderless;

    Assert(_window != nullptr, "Windows was not recreated");
    LOG_INFO("Window was recreated");

    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

Window::State Window::GetState() const
{
    return _state;
}

// ---------------------------------------------------------------------------------------------------------------------

GLFWwindow* Window::GetHandle() const
{
    return _window;
}

// ---------------------------------------------------------------------------------------------------------------------

void Window::AddFramebufferResizedCallback(WindowFramebufferResizedCallback callback)
{
    _framebufferResizedCallbacks.emplace_back(std::move(callback));
}

// ---------------------------------------------------------------------------------------------------------------------

void Window::OnFramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->OnFramebufferResized(width, height);
}

// ---------------------------------------------------------------------------------------------------------------------

void Window::OnFramebufferResized(int, int) const
{
    for (const auto& callback : _framebufferResizedCallbacks)
    {
        callback();
    }
}

// ---------------------------------------------------------------------------------------------------------------------