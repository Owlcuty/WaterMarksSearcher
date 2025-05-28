#pragma once

class IConfiguartionFactory
{
public:
	IConfiguartionFactory() = default;

	virtual IConfiguartionFactory makeSvc() = 0;
};

