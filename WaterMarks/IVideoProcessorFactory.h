#pragma once

#include "IVideoProcessor.h"

#include <memory>


class IVideoProcessorFactory
{
public:
	IVideoProcessorFactory() = default;
	virtual ~IVideoProcessorFactory() {}

	virtual std::unique_ptr<IVideoProcessor> makeSvc() = 0;
};
