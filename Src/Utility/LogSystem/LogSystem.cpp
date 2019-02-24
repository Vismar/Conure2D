#include "LogSystem.hpp"
#include "Utility/IOSystem/IOSystemInterface.hpp"
#include "Utility/Exception/ExceptionHandler.hpp"

using namespace C2D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogSystem::LogSystem(const IOSystemInterface& ioSystem)
: _creationTime(Time::CurrentTime())
, _ioSystem(ioSystem)
, _timeRegex("(%w_time)")
, _logLevelRegex("(%log)")
, _msgRegex("(%msg)")
, _logFileName(std::make_shared<std::string>("LogFile"))
, _logEntryTemplate(std::make_shared<std::string>("[%w_time] %log: %msg \n"))
, _logLevel(LogLevel::Debug)
, _numberOfEntriesToFlush(10)
{
    AddEvent("NewEntryAdded", new Dispatcher<void>());

    // If the exception handler is empty, assign a simple callback that will just write exception error into log
    if (!ExceptionHandler)
    {
        ExceptionHandler =
            [this] (const std::exception& exception)
            {
                this->AddEntry(LogLevel::Error, exception.what());
            };
    }
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

void LogSystem::SetLogFileName(const std::string& newLogFileName)
{
    // Since log system can be called from any thread, log file name should be accessible to change without data race
    const auto newLogFileNamePtr = std::make_shared<std::string>(newLogFileName);
    auto currentLogFileName = std::atomic_load(&_logFileName);
    while (!std::atomic_compare_exchange_weak(&_logFileName, &currentLogFileName, newLogFileNamePtr));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::SetLogEntryTemplate(const std::string& newLogEntryTemplate)
{
    // Since log system can be called from any thread, template should be accessible to change without data race
    const auto newLogEntryTemplatePtr = std::make_shared<std::string>(newLogEntryTemplate);
    auto currentLogEntryTemplate = std::atomic_load(&_logEntryTemplate);
    while (!std::atomic_compare_exchange_weak(&_logEntryTemplate, &currentLogEntryTemplate, newLogEntryTemplatePtr));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::SetNumberOfEntriesToFlush(const uint8_t newNumber)
{
    _numberOfEntriesToFlush = newNumber;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::Flush() const
{
    // Grab current log file name and template
    const auto logFileName = std::atomic_load(&_logFileName);
    const auto logEntryTemplate = std::atomic_load(&_logEntryTemplate);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LogSystem::AddEntry(const LogLevel logLevel, const std::string& message)
{
    if (logLevel >= _logLevel.load())
    {
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
