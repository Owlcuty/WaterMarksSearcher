#pragma once


class IFrameHandlerFactory
{
public:
	IFrameHandlerFactory() = default;
	virtual ~IFrameHandlerFactory() = 0;

	virtual IFrameHandlerFactory makeSvc() = 0;
};

