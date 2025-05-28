#include "ConsoleLogger.h"

#include <filesystem>


ConsoleLogger::ConsoleLogger()
	: ILogger()
{

}

ConsoleLogger::ConsoleLogger(LogLevel level)
	: ILogger()
	, _level(level)
{

}

ConsoleLogger::~ConsoleLogger()
{

}

void ConsoleLogger::log(LogLevel level, const std::string& message, const std::source_location& location)
{
	try
	{
		std::lock_guard _{logMutex};
		if (level <= _level)
		{
			std::filesystem::path file_path(location.file_name());

			std::cout
				<< "[ " << kLogLevelString.at(level) << " ] "
				<< file_path.filename().string() << ":" << location.line() << ":: "
				<< message << std::endl;
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << ":: Log failed" << std::endl;
	}
}