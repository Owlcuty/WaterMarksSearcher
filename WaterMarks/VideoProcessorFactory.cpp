#include "VideoProcessorFactory.h"
#include "VideoProcessorOpenCV.h"


VideoProcessorFactory::VideoProcessorFactory(std::shared_ptr<ILogger> logger)
	: _logger(logger)
{

}

VideoProcessorFactory::~VideoProcessorFactory()
{

}

std::unique_ptr<IVideoProcessor> VideoProcessorFactory::makeSvc()
{
	std::unique_ptr<IVideoProcessor> service = std::make_unique<VideoProcessorOpenCV>(_logger);
	return service;
}