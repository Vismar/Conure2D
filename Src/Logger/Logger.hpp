#pragma once
#include <string_view>
#include <atomic>
#include <experimental/source_location>

class Logger final
{
    using SourceLocation = std::experimental::source_location;
public:
    enum class Level
    {
        Verbose,
        Info,
        Warning,
        Error,
        Critical
    };

    static void ChangeLevel(Level newLevel);

    static void LogVerbose(std::string_view message,
                           std::string_view functionName,
                           const SourceLocation& location = SourceLocation::current());
    static void LogInfo(std::string_view message,
                        std::string_view functionName,
                        const SourceLocation& location = SourceLocation::current());
    static void LogWarning(std::string_view message,
                           std::string_view functionName,
                           const SourceLocation& location = SourceLocation::current());
    static void LogError(std::string_view message,
                         std::string_view functionName,
                         const SourceLocation& location = SourceLocation::current());
    static void LogCritical(std::string_view message,
                            std::string_view functionName,
                            const SourceLocation& location = SourceLocation::current());
    static void Log(Level level,
                    std::string_view message,
                    std::string_view functionName,
                    const SourceLocation& location = SourceLocation::current());

private:
    static void PostLogEntry(std::string_view level,
                             std::string_view message,
                             std::string_view functionName,
                             const SourceLocation& location,
                             std::basic_ostream<char>& output);

    static std::atomic_size_t _logMessageNumber;
    static Level _level;
};