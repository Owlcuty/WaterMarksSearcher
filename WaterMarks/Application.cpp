#include "Application.h"

#include <iostream>
#include <cassert>


Application::Application()
{

}

void Application::run()
{
	try
	{
		_logger->log(ILogger::LogLevel::Info, "Application starts running");

		std::unique_ptr<IVideoProcessor> videoProcessor = _videoProcessorFactory->makeSvc();
		videoProcessor->init("D:\\projects\\WaterMarksSearcher\\example\\videoplayback.mp4");
		std::unique_ptr<IFrame> frame = videoProcessor->getFrame();

		std::unique_ptr<IFrameHandler> frameHandler = _frameHandlerFactory->makeSvc();
		frameHandler->init(std::move(frame));
		frameHandler->handle();
	}
	catch (const std::exception& ex)
	{
		std::string errorMsg = ex.what();
		errorMsg += ":: Application running failed";
		if (_logger)
		{
			_logger->log(ILogger::LogLevel::Error, errorMsg);
		}
		else
		{
			std::cerr << errorMsg << std::endl;
		}
	}
}

#include <iostream>
void Application::setLogger(std::shared_ptr<ILogger> logger)
{
	_logger = logger;
}

void Application::setConfiguartionFactory(std::unique_ptr<IConfiguartionFactory> factory)
{
	_configurationFactory = std::move(factory);
}
void Application::setVideoProcessorFactory(std::unique_ptr<IVideoProcessorFactory> factory)
{
	_videoProcessorFactory = std::move(factory);
}
void Application::setFrameHandlerFactory(std::unique_ptr<IFrameHandlerFactory> factory)
{
	_frameHandlerFactory = std::move(factory);
}
void Application::setWritterFactory(std::unique_ptr<IWritterFactory> factory)
{
	_writterFactory = std::move(factory);
}