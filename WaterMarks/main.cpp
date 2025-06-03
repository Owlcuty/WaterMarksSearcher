#include <iostream>

#include "Application.h"

#include "ConsoleLogger.h"
#include "FileLogger.h"

#include "JsonConfiguration.h"

#include "VideoProcessorFactory.h"
#include "SingleMarkFrameHandlerFactory.h"

#include "FileWriterFactory.h"


void makeLogger(const ConfigData& configData, std::shared_ptr<ILogger>& logger)
{
    switch (configData.log.method)
    {
    case LogMethod::Console:
        logger = std::make_shared<ConsoleLogger>(configData.log.level);
        break;
    case LogMethod::File:
        logger = std::make_shared<FileLogger>(configData.log.path, configData.log.level);
        break;
    default:
        throw std::invalid_argument("Log set failed from config");
    }
}

void makeWriter(const ConfigData& configData, std::unique_ptr<IWriterFactory>& factory, std::shared_ptr<ILogger> logger)
{
    switch (configData.writer.method)
    {
    case WriterMethod::File:
        factory = std::make_unique<FileWriterFactory>(configData.writer.path, logger);
        break;
    default:
        throw std::invalid_argument("Writer set failed from config");
    }
}

int main(int argc, char** argv)
{
    try
    {
        
        JsonConfiguration config{};
        config.init("D:\\tempWM\\config.json");
        ConfigData configData = config.getData();

        Application app {configData};
        
        std::shared_ptr<ILogger> logger{};

        makeLogger(configData, logger);
        app.setLogger(logger);

        std::unique_ptr<IWriterFactory> writerFactory{};
        makeWriter(configData, writerFactory, logger);
        app.setWriterFactory(std::move(writerFactory));

        std::shared_ptr<WatermarkDetector> detector = std::make_shared<WatermarkDetector>(configData.modelPath);

        std::unique_ptr<IVideoProcessorFactory> videoFactory = std::make_unique<VideoProcessorFactory>(logger);
        app.setVideoProcessorFactory(std::move(videoFactory));

        std::unique_ptr<IFrameHandlerFactory> frameHandlerFactory = std::make_unique<SingleMarkFrameHandlerFactory<OpenCvFrame>>(logger, detector);
        app.setFrameHandlerFactory(std::move(frameHandlerFactory));

        app.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << ":: Main failed" << std::endl;
        return -1;
    }
    catch (...)
    {
        return -2;
    }
    return 0;
}
