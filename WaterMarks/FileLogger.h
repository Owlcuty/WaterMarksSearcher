#pragma once

#include "ILogger.h"

#include <fstream>
#include <mutex>


class FileLogger : public ILogger
{
public:
    FileLogger() = default;
    FileLogger(const std::string& path);
    FileLogger(const std::string& path, LogLevel level);
    ~FileLogger() override;

    void log(LogLevel level, const std::string& message, const std::source_location& location = std::source_location::current()) override;

private:
    LogLevel _level{ LogLevel::Info };
    std::string _path{};

    std::mutex logMutex{};
};

