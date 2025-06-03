#pragma once

#include "IWriter.h"

#include <memory>


class IWriterFactory
{
public:
	IWriterFactory() = default;
	virtual ~IWriterFactory() = default;

	virtual std::unique_ptr<IWriter> makeSvc() = 0;
};

