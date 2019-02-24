#pragma once
#include "Utility/Time/Time.hpp"
#include <string>

namespace C2D
{
    /*!
     * \brief Enumeration of possible log levels.
     */
    enum class LogLevel
    {
        Debug = 0, /*!< Debug level. */
        Warning,   /*!< Warning level. */
        Error,     /*!< Error level. */
        Critical   /*!< Critical level. */
    };

    /*! String representation of log levels. */
    const static std::string LogLevelText[] = {"Debug", "Warning", "Error", "Critical"};

    /*!
     * \brief Stores necessary data of log entry.
     */
    struct [[deprecated("Will be reimplemented")]] LogEntry
    {
        LogEntry(const LogEntry& other) = default;
        LogEntry(LogEntry&& other) = default;
        LogEntry& operator=(const LogEntry& other) = default;
        LogEntry& operator=(LogEntry&& other) = default;
        ~LogEntry() = default;

        /*!
         * \brief Default constructor.
         */
        LogEntry();

        /*!
         * \brief Creates new log entry with specified params.
         * \param logLevel - log level of an entry.
         * \param message - message of an entry.
         */
        LogEntry(LogLevel logLevel, std::string&& message);

        /*! Time stamp that was assigned to an entry upon creation. */
        Time timestamp;
        /*! Log level of an entry. */
        LogLevel logLevel;
        /*! Message of an entry. */
        std::string message;
    };
}
