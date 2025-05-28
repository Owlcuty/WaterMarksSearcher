#pragma once

#include "IFrameHandler.h"

#include <memory>


class IFrameHandlerFactory
{
public:
	IFrameHandlerFactory() = default;
	virtual ~IFrameHandlerFactory() = default;

	virtual std::unique_ptr<IFrameHandler> makeSvc() = 0;
};

