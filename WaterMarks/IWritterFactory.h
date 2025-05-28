#pragma once


class IWritterFactory
{
public:
	IWritterFactory() = default;
	virtual ~IWritterFactory() = 0;

	virtual IWritterFactory makeSvc() = 0;
};

