#include "FileLogger.h"

#include <iostream>
#include <filesystem>
#include <iomanip>
#include <ctime>
#include <chrono>

FileLogger::FileLogger(const std::string& path)
    : ILogger()
    , _path(path)
{
    // Создаем директорию для логов, если она не существует
    std::filesystem::path dir = std::filesystem::path(path).parent_path();
    if (!dir.empty() && !std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
    }
}

FileLogger::FileLogger(const std::string& path, LogLevel level)
    : ILogger()
    , _level(level)
    , _path(path)
{
    // Создаем директорию для логов, если она не существует
    std::filesystem::path dir = std::filesystem::path(path).parent_path();
    if (!dir.empty() && !std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);
    }
}

FileLogger::~FileLogger()
{
    // При необходимости можно добавить закрытие файла или другие завершающие действия
}

void FileLogger::log(LogLevel level, const std::string& message, const std::source_location& location)
{
    try
    {
        std::lock_guard<std::mutex> lock(logMutex);

        if (level > _level)
        {
            return; // Не логируем сообщения с уровнем ниже установленного
        }

        // Получаем текущее время
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        // Открываем файл в режиме добавления
        std::ofstream logFile(_path, std::ios_base::app);
        if (!logFile.is_open())
        {
            throw std::runtime_error("Failed to open log file: " + _path);
        }

        // Форматируем запись лога
        struct tm local_tm;
        localtime_s(&local_tm, &now_time);
        logFile << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << now_ms.count()
            << " [ " << kLogLevelString.at(level) << " ] "
            << std::filesystem::path(location.file_name()).filename().string()
            << ":" << location.line()
            << " (" << location.function_name() << ") - "
            << message << std::endl;
    }
    catch (const std::exception& ex)
    {
        // Если не удалось записать в файл, выводим ошибку в консоль
        std::cerr << "FileLogger error: " << ex.what() << " - Original message: " << message << std::endl;
    }
}
