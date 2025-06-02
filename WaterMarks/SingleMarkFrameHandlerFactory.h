#pragma once

#include "IFrameHandlerFactory.h"
#include "ILogger.h"

#include "SingleMarkFrameHandler.h"
#include "OpenCvFrame.h"


template <typename FrameType>
class SingleMarkFrameHandlerFactory : public IFrameHandlerFactory
{
public:
	SingleMarkFrameHandlerFactory() = default;
	SingleMarkFrameHandlerFactory(std::shared_ptr<ILogger> logger)
		: _logger(logger)
	{

	}
	SingleMarkFrameHandlerFactory(std::shared_ptr<ILogger> logger, std::shared_ptr<WatermarkDetector> detector)
		: _logger(logger)
		, _detector(detector)
	{

	}
	~SingleMarkFrameHandlerFactory() = default;

	std::unique_ptr<IFrameHandler> makeSvc() override
	{
		if (_detector)
		{
			return std::make_unique<SingleMarkFrameHandler<FrameType>>(_logger, _detector);
		}
		_log(LogLevel::Error, "No detector!");
		return {};
	}

private:
	void _log(LogLevel level, const std::string& message)
	{
		if (!_logger)
		{
			return;
		}
		_logger->log(level, message);
	}

private:
	std::shared_ptr<ILogger> _logger {};
	std::shared_ptr<WatermarkDetector> _detector {};
};

