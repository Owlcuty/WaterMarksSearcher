#include "FileWriterFactory.h"


FileWriterFactory::FileWriterFactory(const std::string& path)
	: _path(path)
{

}


FileWriterFactory::FileWriterFactory(const std::string& path, std::shared_ptr<ILogger> logger)
	: _path(path)
	, _logger(logger)
{

}

std::unique_ptr<IWriter> FileWriterFactory::makeSvc()
{
	return std::make_unique<FileWriter>(_path);
}