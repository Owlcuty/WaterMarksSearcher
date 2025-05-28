#include "SingleMarkFrameHandlerFactory.h"

#include "SingleMarkFrameHandler.h"


SingleMarkFrameHandlerFactory::SingleMarkFrameHandlerFactory(std::shared_ptr<ILogger> logger)
	: _logger(logger)
{

}

std::unique_ptr<IFrameHandler> SingleMarkFrameHandlerFactory::makeSvc()
{
	std::unique_ptr<IFrameHandler> ret = std::make_unique<SingleMarkFrameHandler<OpenCvFrame>>();
	return ret;
}
