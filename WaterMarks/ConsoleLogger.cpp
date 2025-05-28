#include "ConsoleLogger.h"


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

void ConsoleLogger::log(LogLevel level, const std::string& message)
{
	try
	{
		std::lock_guard _{logMutex};
		if (level <= _level)
		{
			std::cout << message << std::endl;
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << ":: Log failed" << std::endl;
	}
}