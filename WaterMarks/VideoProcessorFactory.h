#pragma once
#include "IVideoProcessorFactory.h"


class VideoProcessorFactory :
    public IVideoProcessorFactory
{
public:
	VideoProcessorFactory();
	~VideoProcessorFactory() override;

	std::unique_ptr<IVideoProcessor> makeSvc() override;
};

