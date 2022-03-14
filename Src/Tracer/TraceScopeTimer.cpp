#include "TraceScopeTimer.hpp"
#include <iostream>

// ---------------------------------------------------------------------------------------------------------------------

TraceScopeTimer::TraceScopeTimer(std::string name)
: _name(std::move(name))
, _start(std::chrono::steady_clock::now())
{ }

// ---------------------------------------------------------------------------------------------------------------------

TraceScopeTimer::~TraceScopeTimer()
{
    auto end = std::chrono::steady_clock::now();
    std::cout << _name << " : " << (end - _start).count() << "ns\n" << std::flush;
}

// ---------------------------------------------------------------------------------------------------------------------