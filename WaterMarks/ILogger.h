#pragma once

#include <string>
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
	virtual ~ILogger() {}

	virtual void log(LogLevel level, const std::string& message) = 0;
};
