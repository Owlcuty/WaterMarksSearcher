#pragma once

#include "ILogger.h"

#include <iostream>
#include <mutex>


class ConsoleLogger :
    public ILogger
{
public:
    ConsoleLogger();
    ConsoleLogger(LogLevel level);
    ~ConsoleLogger() override;

    void log(LogLevel level, const std::string& message, const std::source_location& location = std::source_location::current()) override;

private:
    LogLevel _level {LogLevel::Info};

    std::mutex logMutex {};
};

