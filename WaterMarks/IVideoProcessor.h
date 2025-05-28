#pragma once

#include "IFrame.h"

#include <queue>
#include <string>


class IVideoProcessor
{
public:
	IVideoProcessor() = default;
	virtual ~IVideoProcessor() {}

	virtual void init(const std::string& videoFilePath) = 0;
	virtual std::queue<IFrame> getFrames(std::uint32_t number) = 0;

	virtual std::uint64_t getPosition() const = 0;
	virtual void setPosition(std::uint64_t framePosition) = 0;
};
