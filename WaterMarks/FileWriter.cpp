#include "FileWriter.h"

#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>

FileWriter::FileWriter(const std::string& filePath) : filePath_(filePath)
{
    // Создаем директорию, если она не существует
    std::filesystem::path dir = std::filesystem::path(filePath).parent_path();
    if (!dir.empty() && !std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }

    // Открываем файл в режиме добавления
    outputFile_.open(filePath, std::ios::app);
    if (!outputFile_.is_open()) {
        throw std::runtime_error("Failed to open output file: " + filePath);
    }
}

FileWriter::~FileWriter()
{
    if (outputFile_.is_open()) {
        outputFile_.close();
    }
}

void FileWriter::add(const std::string& message)
{
    std::lock_guard<std::mutex> lock(writeMutex_);
    _writeToFile(message);
    needsCommit_ = true;
}

void FileWriter::add(std::shared_ptr<IFrame> frame)
{
    std::lock_guard<std::mutex> lock(writeMutex_);

    std::stringstream ss;
    ss << "Time of watermark: " << _formatTime(frame->getTime()) << "\n";

    _writeToFile(ss.str());
    needsCommit_ = true;
}

void FileWriter::commit()
{
    std::lock_guard<std::mutex> lock(writeMutex_);
    if (outputFile_.is_open()) {
        outputFile_.flush();
    }
    needsCommit_ = false;
}

void FileWriter::setLogger(std::shared_ptr<ILogger> logger)
{
    _logger = logger;
}

void FileWriter::_log(LogLevel level, const std::string& message)
{
    if (!_logger)
    {
        return;
    }
    _logger->log(level, message);
}

std::string FileWriter::_formatTime(double seconds) const
{
    // Получаем целую часть секунд
    int total_seconds = static_cast<int>(seconds);

    // Вычисляем часы, минуты и секунды
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int secs = total_seconds % 60;

    // Форматируем строку
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << secs;

    return oss.str();
}

void FileWriter::_writeToFile(const std::string& content)
{
    if (!outputFile_.is_open()) {
        throw std::runtime_error("Output file is not open");
    }

    outputFile_ << content;
    if (outputFile_.fail()) {
        throw std::runtime_error("Failed to write to output file");
    }
}
