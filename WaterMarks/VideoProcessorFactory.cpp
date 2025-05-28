#include "VideoProcessorFactory.h"
#include "VideoProcessorOpenCV.h"


VideoProcessorFactory::VideoProcessorFactory()
{

}

VideoProcessorFactory::~VideoProcessorFactory()
{

}

std::unique_ptr<IVideoProcessor> VideoProcessorFactory::makeSvc()
{
	std::unique_ptr<IVideoProcessor> service = std::make_unique<VideoProcessorOpenCV>();
	return service;
}