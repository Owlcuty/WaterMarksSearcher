#pragma once

#include "IFrameHandlerFactory.h"
#include "ILogger.h"

#include "OpenCvFrame.h"


class SingleMarkFrameHandlerFactory : public IFrameHandlerFactory
{
public:
	SingleMarkFrameHandlerFactory() = default;
	SingleMarkFrameHandlerFactory(std::shared_ptr<ILogger> logger);
	~SingleMarkFrameHandlerFactory() = default;

	std::unique_ptr<IFrameHandler> makeSvc() override;

private:
	void _log(ILogger::LogLevel level, const std::string& message);

private:
	std::shared_ptr<ILogger> _logger{};
};

