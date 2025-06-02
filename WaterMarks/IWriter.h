#pragma once

#include "IFrame.h"

#include <string>
#include <memory>



class IWriter
{
public:
	IWriter() = default;
	virtual ~IWriter() = default;

	virtual void add(const std::string& message) = 0;
	virtual void add(std::unique_ptr<IFrame> frame) = 0;

	virtual void commit() = 0;
};
