#pragma once

#include "IWriter.h"
#include "ILogger.h"

#include <fstream>
#include <mutex>
#include <string>

/**
 * @brief Реализация интерфейса IWriter для записи данных в файл
 *
 * Класс обеспечивает:
 * - Потокобезопасную запись через std::mutex
 * - Форматирование временных меток из IFrame
 * - Автоматическое создание директорий
 * - Гарантированную запись через commit()
 */
class FileWriter : public IWriter
{
public:
    explicit FileWriter(const std::string& filePath);

    ~FileWriter() override;

    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    void add(const std::string& message) override;
    void add(std::shared_ptr<IFrame> frame) override;

    void setLogger(std::shared_ptr<ILogger> logger) override;

    void commit() override;

private:
    void _log(LogLevel level, const std::string& message);

private:
    std::shared_ptr<ILogger> _logger{};
    std::string _formatTime(double timestamp) const;

    void _writeToFile(const std::string& content);

    std::string filePath_;          ///< Путь к выходному файлу
    std::ofstream outputFile_;      ///< Поток вывода в файл
    mutable std::mutex writeMutex_; ///< Мьютекс для потокобезопасности
    bool needsCommit_ = false;      ///< Флаг необходимости сброса на диск
};
