#include "Logger.hpp"
#include <iostream>
#include <thread>

// ---------------------------------------------------------------------------------------------------------------------

constexpr std::string_view infoLevel = "Info";
constexpr std::string_view traceLevel = "Trace";
constexpr std::string_view warningLevel = "Warning";
constexpr std::string_view errorLevel = "Error";
constexpr std::string_view criticalLevel = "Critical";
constexpr std::string_view unknownLevel = "Unknown logger level";

// ---------------------------------------------------------------------------------------------------------------------

constexpr std::string_view GetLoggerLevelAsString(Logger::Level level)
{
    switch (level)
    {
        case Logger::Level::Info:
            return infoLevel;
        case Logger::Level::Trace:
            return traceLevel;
        case Logger::Level::Warning:
            return warningLevel;
        case Logger::Level::Error:
            return errorLevel;
        case Logger::Level::Critical:
            return criticalLevel;
    }

    return unknownLevel;
}

// ---------------------------------------------------------------------------------------------------------------------

std::atomic_size_t Logger::_logMessageNumber = 0;
Logger::Level Logger::_level = Logger::Level::Info;

// ---------------------------------------------------------------------------------------------------------------------

void Logger::ChangeLevel(Level newLevel)
{
    _level = newLevel;
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogInfo(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level > Level::Info)
    {
        return;
    }
    PostLogEntry(GetLoggerLevelAsString(Level::Info), message, functionName, location, std::cout);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogTrace(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level > Level::Trace)
    {
        return;
    }
    PostLogEntry(GetLoggerLevelAsString(Level::Trace), message, functionName, location, std::cout);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogWarning(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level > Level::Warning)
    {
        return;
    }
    PostLogEntry(GetLoggerLevelAsString(Level::Warning), message, functionName, location, std::cerr);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogError(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level > Level::Error)
    {
        return;
    }
    PostLogEntry(GetLoggerLevelAsString(Level::Error), message, functionName, location, std::cerr);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogCritical(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level > Level::Critical)
    {
        return;
    }
    PostLogEntry(GetLoggerLevelAsString(Level::Critical), message, functionName, location, std::cerr);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::PostLogEntry(std::string_view level,
                          std::string_view message,
                          std::string_view functionName,
                          const SourceLocation& location,
                          std::basic_ostream<char>& output)
{
    output << "[Level: " << level << "] [Thread-id: "
           << std::this_thread::get_id() << "] [#"
           << _logMessageNumber++ << "]\n"
           << location.file_name() << ':' << location.line() << "\n"
           << (functionName.empty() ? location.function_name() : functionName) << "\n\t"
           << message << "\n\n";

    output.flush();
}

// ---------------------------------------------------------------------------------------------------------------------