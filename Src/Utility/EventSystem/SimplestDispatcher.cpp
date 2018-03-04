#include "SimplestDispatcher.hpp"
#include "Utility/Containers/AnyCallable.hpp"
#include <any>

using namespace Utility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SimplestDispatcher::Invoke()
{
    for (auto iter = _callables.begin(); iter != _callables.end(); )
    {
        try
        {
            (*iter)();
            ++iter;
        }
        catch (const std::bad_any_cast& exception)
        {
            // TODO: Handle error when log system will be introduced
            (void)exception.what();
            iter = _callables.erase(iter);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
