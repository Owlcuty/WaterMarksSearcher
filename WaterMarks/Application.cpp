#include "Application.h"

#include <iostream>
#include <cassert>
#include <queue>
#include <omp.h>


Application::Application(const ConfigData& configData)
	: _configData(configData)
{

}

#include <opencv2/opencv.hpp>
#include "Profiler.hpp"

void Application::run()
{
	try
	{
		if (!_logger)
		{
			throw "No logger";
		}
		_logger->log(LogLevel::Info, "Application starts running");


		if (!_videoProcessorFactory)
		{
			throw "No videoprocessor's factory";
		}
		std::unique_ptr<IVideoProcessor> videoProcessor = _videoProcessorFactory->makeSvc();
		if (!videoProcessor)
		{
			throw "Factory couldn't make videoprocessor";
		}
		videoProcessor->init(_configData.videoPath);
		const std::int32_t chunkSize = 128;
		std::vector<std::unique_ptr<IFrame>> frames(chunkSize);
		std::int32_t frameIdx = 0;
		while (1)
		{
			//PROFILE_START("Get frame");
			std::unique_ptr<IFrame> frame = videoProcessor->getFrame();
			//PROFILE_END();
			if (!frame)
			{
				break;
			}
			frames[frameIdx] = std::move(frame);
			videoProcessor->skipFrames(24);
			frameIdx++;
			
			if (frameIdx < chunkSize)
			{
				continue;
			}
			PROFILE_START("FOR HANDLE");
#ifdef _OPENMP
			//#pragma omp parallel for
#endif
			for (std::int32_t idx = 0; idx < chunkSize; idx++)
			{
				if (!_frameHandlerFactory)
				{
					throw "No frame handler's factory";
				}
				std::unique_ptr<IFrameHandler> frameHandler = _frameHandlerFactory->makeSvc();
				if (!frameHandler)
				{
					throw "Factory couldn't make frame handler";
				}
				double time = frames[idx]->getTime();
				frameHandler->setFrame(std::move(frames[idx]));
				bool gotMark = frameHandler->handle();
				if (gotMark)
				{
					std::string msg = "Time of watermark: " + std::to_string(static_cast<int>(time) / 60) + ":" + std::to_string(time - static_cast<int>(time) / 60 * 60);
					_logger->log(LogLevel::Info, msg);
				}
			}
			PROFILE_END();
			PROFILE_PRINT();
			frameIdx = 0;
		}
	}
	catch (const std::exception& ex)
	{
		std::string errorMsg = ex.what();
		errorMsg += ":: Application running failed";
		if (_logger)
		{
			_logger->log(LogLevel::Error, errorMsg);
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

void Application::setVideoProcessorFactory(std::unique_ptr<IVideoProcessorFactory> factory)
{
	_videoProcessorFactory = std::move(factory);
}
void Application::setFrameHandlerFactory(std::unique_ptr<IFrameHandlerFactory> factory)
{
	_frameHandlerFactory = std::move(factory);
}
void Application::setWriterFactory(std::unique_ptr<IWriterFactory> factory)
{
	_writerFactory = std::move(factory);
}
