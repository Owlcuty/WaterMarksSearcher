#pragma once

#include "IFrame.h"

#include <memory>


class IFrameHandler
{
public:
	virtual ~IFrameHandler() = default;
	virtual void init(std::unique_ptr<IFrame> frame) = 0;
	virtual void handle() = 0;
};