#pragma once
#include <ios>

namespace Utility
{
    /*!
     * \brief Public interface for IO system.
     */
    class IOSystemInterface
    {
    public:
        IOSystemInterface(const IOSystemInterface& other) = delete;
        IOSystemInterface(IOSystemInterface&& other) = delete;
        IOSystemInterface& operator=(const IOSystemInterface& other) = delete;
        IOSystemInterface& operator=(IOSystemInterface&& other) = delete;
        IOSystemInterface() = default;
        virtual  ~IOSystemInterface() = default;

        /*!
         * \brief Writes data to a text file.
         * \param fileName - file name to which data should be written.
         * \param data - data that should be written to a text file.
         * \param openMode - mode in which a text file should be opened.
         */
        virtual void WriteToTextFile(std::string&& fileName, 
                                     std::string&& data, 
                                     std::ios_base::openmode openMode = std::ios_base::app) const = 0;
    };
}
