#include "AnyCallableHandler.hpp"

using namespace Utility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AnyCallableHandler::operator==(const AnyCallableHandler& other) const
{
    bool equal = false;

    // We should check first inner handlers if both AnyCallableHandlers contains at least something
    if ((_firstHandler != 0) && (other._firstHandler != 0))
    {
        // We should check second inner handlers if both AnyCallableHandlers do not contains nullptr
        if ((_secondHandler != nullptr) && (other._secondHandler != nullptr))
        {
            equal = ((_firstHandler == other._firstHandler) && (_secondHandler == other._secondHandler));
        }
        // Even if one of two AnyCallableHandlers contains second inner handler, first inner handlers will not be equal
        else
        {
            equal = (_firstHandler == other._firstHandler);
        }
    }

    return equal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AnyCallableHandler::IsHandling() const
{
    return (_firstHandler != 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
