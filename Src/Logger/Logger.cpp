#include "Logger.hpp"
#include <iostream>
#include <thread>

// ---------------------------------------------------------------------------------------------------------------------

constexpr std::string_view verboseLevel = "Verbose";
constexpr std::string_view infoLevel = "Info";
constexpr std::string_view warningLevel = "Warning";
constexpr std::string_view errorLevel = "Error";
constexpr std::string_view criticalLevel = "Critical";
constexpr std::string_view unknownLevel = "Unknown logger level";

// ---------------------------------------------------------------------------------------------------------------------

constexpr std::string_view GetLoggerLevelAsString(Logger::Level level)
{
    switch (level)
    {
        case Logger::Level::Verbose:
            return verboseLevel;
        case Logger::Level::Info:
            return infoLevel;
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

void Logger::LogVerbose(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    Log(Level::Verbose, message, functionName, location);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogInfo(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    Log(Level::Info, message, functionName, location);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogWarning(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    Log(Level::Warning, message, functionName, location);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogError(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    Log(Level::Error, message, functionName, location);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::LogCritical(std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    Log(Level::Critical, message, functionName, location);
}

// ---------------------------------------------------------------------------------------------------------------------

void Logger::Log(Level level, std::string_view message, std::string_view functionName, const SourceLocation& location)
{
    if (_level <= level)
    {
        std::basic_ostream<char>* output = &std::cout;
        switch (level)
        {
            case Level::Verbose:
            case Level::Info:
                output = &std::cout;
                break;
            case Level::Warning:
            case Level::Error:
            case Level::Critical:
                output = &std::cerr;
                break;
        }

        PostLogEntry(GetLoggerLevelAsString(level), message, functionName, location, *output);
    }
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