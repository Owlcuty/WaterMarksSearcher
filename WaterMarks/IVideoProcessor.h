#pragma once

#include "IFrame.h"

#include <memory>
#include <string>


class IVideoProcessor
{
public:
	IVideoProcessor() = default;
	virtual ~IVideoProcessor() = default;

	virtual void init(const std::string& videoFilePath) = 0;
	virtual std::unique_ptr<IFrame> getFrame() = 0;

	virtual std::uint64_t getPosition() const = 0;
	virtual void setPosition(std::uint64_t framePosition) = 0;

	virtual void skipFrames(std::uint32_t frameSkip) = 0;
};
