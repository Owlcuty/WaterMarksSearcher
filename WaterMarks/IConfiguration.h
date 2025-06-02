#pragma once

#include "ILogger.h"

#include <string>


enum class WriterMethod
{
	Console,
	File,
	CSV,
	XML,
	JSon
};

struct WriterData
{
	WriterMethod method;
	std::string path;
};

enum class LogMethod
{
	Console,
	File
};

struct LogData
{
	LogMethod method;
	LogLevel level;
	std::string path;
};

struct ConfigData
{
	std::string modelPath;
	std::string videoPath;
	LogData log;
	WriterData writer;
};

class IConfiguration
{
public:
	IConfiguration() = default;
	virtual ~IConfiguration() = default;

	virtual void init(const std::string& path) = 0;
	virtual const ConfigData& getData() const = 0;
};