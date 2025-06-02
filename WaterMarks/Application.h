#pragma once

#include "ILogger.h"
#include "IConfiguration.h"
#include "IVideoProcessorFactory.h"
#include "IFrameHandlerFactory.h"
#include "IWriterFactory.h"

#include <memory>


class Application
{
public:
	Application(const ConfigData& configData);
	~Application() = default;

	void run();

	void setLogger(std::shared_ptr<ILogger> logger);
	void setVideoProcessorFactory(std::unique_ptr<IVideoProcessorFactory> factory);
	void setFrameHandlerFactory(std::unique_ptr<IFrameHandlerFactory> factory);
	void setWriterFactory(std::unique_ptr<IWriterFactory> factory);

private:
	ConfigData _configData{};

	std::shared_ptr<ILogger> _logger;

	std::unique_ptr<IVideoProcessorFactory> _videoProcessorFactory;
	std::unique_ptr<IFrameHandlerFactory> _frameHandlerFactory;
	std::unique_ptr<IWriterFactory> _writerFactory;
};

