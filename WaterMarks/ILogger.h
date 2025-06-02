#pragma once

#include <source_location>
#include <string>
#include <unordered_map>
#include <cstdint>


enum class LogLevel : std::uint32_t
{
	Error,
	Warning,
	Info,
	Debug,
	Debug2,
	Debug4,
	Debug8,
	Debug16,
};

class ILogger
{
public:

	ILogger() = default;
	virtual ~ILogger() = default;

	virtual void log(LogLevel level, const std::string& message, const std::source_location& location = std::source_location::current()) = 0;
};

const std::unordered_map<LogLevel, std::string> kLogLevelString = {
	{LogLevel::Error, "Error"},
	{LogLevel::Warning, "Warning"},
	{LogLevel::Info, "Info"},
	{LogLevel::Debug, "Debug"},
	{LogLevel::Debug2, "Debug2"},
	{LogLevel::Debug4, "Debug4"},
	{LogLevel::Debug8, "Debug8"},
	{LogLevel::Debug16, "Debug16"}
};
