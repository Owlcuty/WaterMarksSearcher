#pragma once

#include "IVideoProcessor.h"
#include "ILogger.h"

#include <memory>


class VideoProcessorOpenCV :
    public IVideoProcessor
{
public:
	VideoProcessorOpenCV() = default;
	VideoProcessorOpenCV(std::shared_ptr<ILogger> logger);
	~VideoProcessorOpenCV() override;

	void init(const std::string& videoFilePath) override;
	std::queue<IFrame> getFrames(std::uint32_t number) override;

	std::uint64_t getPosition() const override;
	void setPosition(std::uint64_t framePosition) override;

private:
	bool _openMedia();
	void _log(ILogger::LogLevel level, const std::string& message);

private:
	std::string _path {};
	std::uint64_t _position {};
	std::shared_ptr<ILogger> _logger;
};
