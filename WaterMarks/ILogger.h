#pragma once

#include <source_location>
#include <string>
#include <unordered_map>
#include <cstdint>


class ILogger
{
public:
	enum class LogLevel : std::uint32_t
	{
		Error,
		Warning,
		Info,
		Debug
	};

	ILogger() = default;
	virtual ~ILogger() = default;

	virtual void log(LogLevel level, const std::string& message, const std::source_location& location = std::source_location::current()) = 0;
};

const std::unordered_map<ILogger::LogLevel, std::string> kLogLevelString = {
	{ILogger::LogLevel::Error, "Error"},
	{ILogger::LogLevel::Warning, "Warning"},
	{ILogger::LogLevel::Info, "Info"},
	{ILogger::LogLevel::Debug, "Debug"}
};
