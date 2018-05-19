#pragma once
#include "Utility/EventSystem/EventManager.hpp"
#include "Utility/LogSystem/LogEntry.hpp"
#include <memory>
#include <atomic>

namespace Utility
{
    template <class T>
    class LockFreeLinkedQueue;

    /*!
     * \brief Thread-safe log system which handles creating and storing logs of all events that occur.
     */
    class LogSystem : public EventManager
    {
    public:
        LogSystem(const LogSystem& other) = delete;
        LogSystem(LogSystem&& other) = delete;
        LogSystem& operator=(const LogSystem& other) = delete;
        LogSystem& operator=(LogSystem&& other) = delete;
        ~LogSystem() = default;

        /*!
         * \brief Default constructor.
         */
        LogSystem();

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
        void Flush();

    private:
        /*! Current log level of log system. */
        std::atomic<LogLevel> _logLevel;
        /*! Number of log entries that will stored before flushing. */
        std::atomic_uint8_t _numberOfEntriesToFlush;
        /*! Linked queue of log entries. */
        std::unique_ptr<LockFreeLinkedQueue<LogEntry>> _msgQueue;
    };
}