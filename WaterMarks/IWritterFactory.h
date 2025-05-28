#pragma once


class IWritterFactory
{
public:
	IWritterFactory() = default;
	virtual ~IWritterFactory() = default;

	virtual IWritterFactory makeSvc() = 0;
};

