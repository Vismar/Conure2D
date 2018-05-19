#include "LogSystem.hpp"
#include "Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp"

using namespace Utility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogSystem::LogSystem() 
: _logLevel(LogLevel::Debug)
, _numberOfEntriesToFlush(5)
, _msgQueue(std::make_unique<LockFreeLinkedQueue<LogEntry>>())
{
    AddEvent("NewEntryAdded", new Dispatcher<void>());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::SetLogLevel(const LogLevel logLevel)
{
    _logLevel = logLevel;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogLevel LogSystem::GetLogLevel() const
{
    return _logLevel.load();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::SetNumberOfEntriesToFlush(const uint8_t newNumber)
{
    auto oldNumber = _numberOfEntriesToFlush.load();
    while (!_numberOfEntriesToFlush.compare_exchange_weak(oldNumber, newNumber));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::Flush()
{
    while (auto logEntry = _msgQueue->PopFront())
    {
        //TODO: Implement when IOSystem will be implemented
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::AddEntry(const LogLevel logLevel, const std::string& message)
{
    if (logLevel >= _logLevel)
    {
        _msgQueue->EmplaceBack(LogEntry(logLevel, std::string(message)));
        InvokeEvent<void, LogEntry>("NewEntryAdded", LogEntry(logLevel, std::string(message)));
        if (_msgQueue->GetSize() >= _numberOfEntriesToFlush.load())
        {
            Flush();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
