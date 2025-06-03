#pragma once

#include "IFrame.h"
#include "ILogger.h"

#include <string>
#include <memory>



class IWriter
{
public:
	IWriter() = default;
	virtual ~IWriter() = default;

	virtual void add(const std::string& message) = 0;
	virtual void add(std::shared_ptr<IFrame> frame) = 0;

	virtual void setLogger(std::shared_ptr<ILogger> logger) = 0;

	virtual void commit() = 0;
};
