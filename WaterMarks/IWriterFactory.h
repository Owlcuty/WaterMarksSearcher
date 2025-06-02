#pragma once


class IWriterFactory
{
public:
	IWriterFactory() = default;
	virtual ~IWriterFactory() = default;

	virtual IWriterFactory makeSvc() = 0;
};

