#pragma once

#include "IConfiguration.h"
#include "ILogger.h"

#include <memory>


class JsonConfiguration : public IConfiguration
{
public:
	JsonConfiguration() = default;
	~JsonConfiguration();

	void init(const std::string& path) override;
	const ConfigData& getData() const override;

private:
	ConfigData _data;
};