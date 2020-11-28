#pragma once
#include <string>
#include <chrono>

class TraceScopeTimer final
{
public:
    explicit TraceScopeTimer(std::string name);
    ~TraceScopeTimer();

private:
    std::string _name;
    std::chrono::steady_clock::time_point _start;
};

#define TraceIt TraceScopeTimer traceTimer(__PRETTY_FUNCTION__)