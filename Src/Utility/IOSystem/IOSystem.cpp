#include "IOSystem.hpp"
#include <thread>
#include <chrono>

using namespace Utility;
using namespace std::chrono_literals;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IOSystem::IOSystem()
: _turnedOn(false)
, _isRunning(false)
, _textWriteStream({"", std::ios_base::out, std::fstream()})
, _textWriteQueue(std::make_unique<LockFreeLinkedQueue<TextEntry>>())
{ }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IOSystem::Start()
{
    // Start IO thread only if it was not started previously
    if (!IsRunning())
    {
        // Start IO thread
        _turnedOn = true;
        std::thread logicThread(&IOSystem::_Loop, this);
        logicThread.detach();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IOSystem::IsRunning() const
{
    return _turnedOn.load() || _isRunning.load() || !_textWriteQueue->IsEmpty();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IOSystem::Stop()
{
    _turnedOn = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IOSystem::WriteToTextFile(std::string&& fileName, std::string&& data, const std::ios_base::openmode openMode) const
{
    switch (openMode)
    {
    case std::ios_base::app:
    case std::ios_base::ate:
    case std::ios_base::trunc:
        _textWriteQueue->EmplaceBack({ fileName, data, openMode });
        break;
    default:
        // All other flags should be ignored
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IOSystem::_Loop()
{
    // If thread is ON or queues still have something to write to files
    while (_turnedOn.load() || !_textWriteQueue->IsEmpty())
    {
        // Mark system is "running"
        _isRunning = true;

        // If we have something to write to a text files, do it
        if (!_textWriteQueue->IsEmpty())
        {
            _WriteTextData();
        }

        // Work finished
        _isRunning = false;

        // If we do not have anything to do right now, sleep and close all streams
        if (_textWriteQueue->IsEmpty())
        {
            std::this_thread::sleep_for(10ms);
            _textWriteStream.stream.close();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IOSystem::_WriteTextData()
{
    // Try to get all entries from a queue
    while (const auto textEntry = _textWriteQueue->PopFront())
    {
        // Only if entry has a file name we should do stuff
        if (!textEntry->fileName.empty())
        {
            // We should close and clear stream flags if entry supposed to be written in different file or with different mode
            if ((_textWriteStream.fileName != textEntry->fileName) ||
                !(_textWriteStream.openMode & textEntry->openMode))
            {
                _textWriteStream.stream.close();
                _textWriteStream.stream.clear();
            }

            // If stream is not opened, we should reopen it with required file name and mode
            if (!_textWriteStream.stream.is_open())
            {
                _textWriteStream.fileName = textEntry->fileName;
                _textWriteStream.openMode = std::ios_base::out | textEntry->openMode;
                _textWriteStream.stream.open(textEntry->fileName, _textWriteStream.openMode);
            }

            // Write data to a file
            _textWriteStream.stream << textEntry->data.c_str();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
