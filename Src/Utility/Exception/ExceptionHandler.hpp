#pragma once
#include <functional>

namespace C2D
{
    /*! Simple callback that can be changed to whatever the user wants it to be to handle exceptions. */
    [[deprecated("Will be removed")]]
    static std::function<void(const std::exception&)> ExceptionHandler;
} 