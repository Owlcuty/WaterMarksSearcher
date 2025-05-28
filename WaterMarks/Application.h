#pragma once

#include "ILogger.h"
#include "IConfiguartionFactory.h"
#include "IVideoProcessorFactory.h"
#include "IFrameHandlerFactory.h"
#include "IWritterFactory.h"

#include <memory>


class Application
{
public:
	Application();
	~Application() = default;

	void run();

	void setLogger(std::shared_ptr<ILogger> logger);
	void setConfiguartionFactory(std::unique_ptr<IConfiguartionFactory> factory);
	void setVideoProcessorFactory(std::unique_ptr<IVideoProcessorFactory> factory);
	void setFrameHandlerFactory(std::unique_ptr<IFrameHandlerFactory> factory);
	void setWritterFactory(std::unique_ptr<IWritterFactory> factory);

private:
	std::shared_ptr<ILogger> _logger;

	std::unique_ptr<IConfiguartionFactory> _configurationFactory;
	std::unique_ptr<IVideoProcessorFactory> _videoProcessorFactory;
	std::unique_ptr<IFrameHandlerFactory> _frameHandlerFactory;
	std::unique_ptr<IWritterFactory> _writterFactory;
};

