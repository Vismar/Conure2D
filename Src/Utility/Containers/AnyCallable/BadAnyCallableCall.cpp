#include "BadAnyCallableCall.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* BadAnyCallableCall::what() const noexcept
{
    return _exceptionMessage.c_str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
