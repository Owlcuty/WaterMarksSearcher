#pragma once

#include "IFrame.h"

#include <memory>


class IFrameHandler
{
public:
	virtual ~IFrameHandler() = default;
	virtual void setFrame(std::unique_ptr<IFrame> frame) = 0;
	virtual bool handle() = 0;
};