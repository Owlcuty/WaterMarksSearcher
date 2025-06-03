#pragma once

#include "IWriterFactory.h"
#include "FileWriter.h"
#include "ILogger.h"


class FileWriterFactory : public IWriterFactory
{
public:
	FileWriterFactory(const std::string& path);
	FileWriterFactory(const std::string& path, std::shared_ptr<ILogger> logger);
	~FileWriterFactory() override = default;

	std::unique_ptr<IWriter> makeSvc() override;

private:
	std::string _path{};
	std::shared_ptr<ILogger> _logger;
};