#pragma once
#include "Utility/IOSystem/IOSystemInterface.hpp"
#include "Utility/Containers/LockFreeLinkedQueue/LockFreeLinkedQueue.hpp"
#include <fstream>
#include <atomic>

namespace Utility
{
    /*!
     * \brief System which works in separate thread and provides functionality
     *        to write and read data from text and binary files.
     */
    class IOSystem final : public IOSystemInterface
    {
    public:
        IOSystem(const IOSystem& other) = delete;
        IOSystem(IOSystem&& other) = delete;
        IOSystem& operator=(const IOSystem& other) = delete;
        IOSystem& operator=(IOSystem&& other) = delete;
        ~IOSystem() = default;

        /*!
         * \brief Default constructor.
         */
        IOSystem();

        /*!
         * \brief Runs the IO system in separate thread.
         */
        void Start();

        /*!
         * \brief Check if IO thread is still running.
         * \return True if IOSystem not turned off or still have something to do.
         */
        bool IsRunning() const;

        /*!
         * \brief Stops IO thread.
         * 
         * Marks IO thread to turn off, but thread will continue its work to prevent loss of data.
         */
        void Stop();

        /*!
         * \brief Writes data to a text file.
         * \param fileName - file name to which data should be written.
         * \param data - data that should be written to a text file.
         * \param openMode - mode in which a text file should be opened.
         */
        void WriteToTextFile(std::string&& fileName, 
                             std::string&& data, 
                             std::ios_base::openmode openMode) const final;

    private:
        /*!
         * \brief Loops through all queues and streams.
         */
        void _Loop();

        /*!
         * \brief Writes all entries from queue to text files.
         */
        void _WriteTextData();

        /*!
         * \brief Utility struct which stores required info about text stream.
         */
        struct TextStream
        {
            /*! File name which was previously used by text stream. */
            std::string fileName;
            /*! Open mode which was used previously by text stream. */
            std::ios_base::openmode openMode = std::ios_base::out;
            /*! Text stream. */
            std::fstream stream;
        };

        /*!
         * \brief Utility struct which stores required data to be written in text file.
         */
        struct TextEntry
        {
            /*! File name to which data should be written. */
            std::string fileName;
            /*! Data which will be written to a text file. */
            std::string data;
            /*! Open mode in which text stream will write data to a text file. */
            std::ios_base::openmode openMode = std::ios_base::out;
        };

        /*! Flag defines if IOSystem is still turned on. */
        std::atomic_bool _turnedOn;
        /*! Flag defines if IOSystem currently doing stuff. */
        std::atomic_bool _isRunning;
        /*! A stream which is used to write data to text files. */
        TextStream _textWriteStream;
        /*! A queue which contains entries that should be written to text files. */
        std::unique_ptr<LockFreeLinkedQueue<TextEntry>> _textWriteQueue;
    };
}
