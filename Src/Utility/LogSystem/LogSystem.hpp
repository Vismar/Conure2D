#pragma once
#include "Utility/EventSystem/EventManager.hpp"
#include "Utility/LogSystem/LogEntry.hpp"
#include "Utility/LogSystem/LogUtilities.hpp"
#include <memory>
#include <atomic>
#include <regex>

namespace Utility
{
    class IOSystemInterface;
    template <class T>
    class LockFreeLinkedQueue;

    /*!
     * \brief Thread-safe log system which handles creating and storing logs of all events that occur.
     */
    class LogSystem final : public EventManager
    {
    public:
        LogSystem() = delete;
        LogSystem(const LogSystem& other) = delete;
        LogSystem(LogSystem&& other) = delete;
        LogSystem& operator=(const LogSystem& other) = delete;
        LogSystem& operator=(LogSystem&& other) = delete;
        ~LogSystem() final = default;

        /*!
         * \brief Default constructor.
         */
        explicit LogSystem(const IOSystemInterface& ioSystem);

        /*!
         * \brief Set new log level.
         * \param logLevel - new log level which will used by log system.
         */
        void SetLogLevel(LogLevel logLevel);

        /*!
         * \brief Gets current log level of log system.
         * \return Log level which is currently used by log system.
         */
        LogLevel GetLogLevel() const;

        /*!
         * \brief Sets a new log file name.
         * \param newLogFileName - new log file name which will be used by log system.
         */
        void SetLogFileName(const std::string& newLogFileName);

        /*!
         * \brief Sets new log entry template.
         * \param newLogEntryTemplate - new template which will be used to create log entries by log system.
         * 
         * Template can contain next variables:
         *   - %w_time - will be replaced by a time when entry was added to log system since start of the app.
         *   - %log - will be replaced by a log level.
         *   - %msg - will be replaced by an actual log entry message.
         */
        void SetLogEntryTemplate(const std::string& newLogEntryTemplate);

        /*!
         * \brief Sets number of entries that will be stored before flushing them.
         * \param newNumber - new number which will be used.
         */
        void SetNumberOfEntriesToFlush(uint8_t newNumber);

        /*!
         * \brief Adds a new log entry.
         * \param logLevel - log level of a new entry.
         * \param message - message of a new entry.
         */
        void AddEntry(LogLevel logLevel, const std::string& message);

        /*!
         * \brief Flushes all stored entries to the log file.
         */
        void Flush() const;

    private:
        /*! Moment of the creation of the log system. */
        const Time _creationTime;
        /*! Const reference to the IOSystem. */
        const IOSystemInterface& _ioSystem;
        /*! Regex for time. */
        const std::regex _timeRegex;
        /*! Regex for log level. */
        const std::regex _logLevelRegex;
        /*! Regex for message. */
        const std::regex _msgRegex;
        /*! Name of a log file which is used by log system. */
        std::shared_ptr<std::string> _logFileName;
        /*! Template which is used by log system to create log entries. */
        std::shared_ptr<std::string> _logEntryTemplate;
        /*! Current log level of log system. */
        std::atomic<LogLevel> _logLevel;
        /*! Number of log entries that will stored before flushing. */
        std::atomic_uint8_t _numberOfEntriesToFlush;
        /*! Linked queue of log entries. */
        std::unique_ptr<LockFreeLinkedQueue<LogEntry>> _msgQueue;
    };
}
