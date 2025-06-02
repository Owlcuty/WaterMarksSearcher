#include "JsonConfiguration.h"
#include "ILogger.h"

#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

JsonConfiguration::~JsonConfiguration() = default;

namespace
{
    const std::unordered_map<std::string, WriterMethod> kJsonToEnum = {
        {"console", WriterMethod::Console},
        {"file", WriterMethod::File},
        {"csv", WriterMethod::CSV},
        {"json", WriterMethod::JSon},
        {"xml", WriterMethod::XML}
    };
    const std::unordered_map<std::string, LogLevel> kJsonToLogLevel = {
        {"Error", LogLevel::Error},
        {"Warning", LogLevel::Warning},
        {"Info", LogLevel::Info},
        {"Debug", LogLevel::Debug},
        {"Debug2", LogLevel::Debug2},
        {"Debug4", LogLevel::Debug4},
        {"Debug8", LogLevel::Debug8},
        {"Debug16", LogLevel::Debug16}
    };
}

void JsonConfiguration::init(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open configuration file: " + path);
    }

    try
    {
        json config;
        file >> config;

        // Парсинг основных параметров
        _data.modelPath = config.value("modelPath", "");
        _data.videoPath = config.value("videoPath", "");

        // Парсинг настроек логгера
        if (config.contains("log"))
        {
            auto& logConfig = config["log"];
            std::string logMethod = logConfig.value("method", "Console");
            if (logMethod == "File")
            {
                _data.log.method = LogMethod::File;
            }
            else
            {
                _data.log.method = LogMethod::Console;
            }
            _data.log.path = logConfig.value("path", "");
            _data.log.level = kJsonToLogLevel.at(logConfig.value("level", "Info"));
        }

        // Парсинг настроек writer
        if (config.contains("writer"))
        {
            auto& writerConfig = config["writer"];
            std::string writerMethod = writerConfig.value("method", "Console");
            std::transform(writerMethod.begin(), writerMethod.end(), writerMethod.begin(),
                [](unsigned char c) { return std::tolower(c); });
            _data.writer.method = kJsonToEnum.at(writerMethod);
            _data.writer.path = writerConfig.value("path", "");
        }
    }
    catch (const json::exception& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
}

const ConfigData& JsonConfiguration::getData() const {
    return _data;
}

