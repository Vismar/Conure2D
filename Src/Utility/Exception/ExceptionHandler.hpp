#pragma once
#include <functional>

namespace Conure::Utility
{
    /*! Simple callback that can be changed to whatever the user wants it to be to handle exceptions. */
    static std::function<void(const std::exception&)> ExceptionHandler;
} 