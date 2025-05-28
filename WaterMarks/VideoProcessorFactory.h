#pragma once
#include "IVideoProcessorFactory.h"
#include "ILogger.h"


class VideoProcessorFactory :
    public IVideoProcessorFactory
{
public:
	VideoProcessorFactory() = default;
	VideoProcessorFactory(std::shared_ptr<ILogger> logger);
	~VideoProcessorFactory() override;

	std::unique_ptr<IVideoProcessor> makeSvc() override;

private:
	std::shared_ptr<ILogger> _logger {};
};

