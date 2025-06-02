#pragma once

#include "IWriter.h"

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
    /**
     * @brief Конструктор с открытием файла
     * @param filePath Путь к выходному файлу
     * @throws std::runtime_error При ошибке открытия файла
     */
    explicit FileWriter(const std::string& filePath);

    /**
     * @brief Деструктор с закрытием файла
     */
    ~FileWriter() override;

    // Удаляем копирование и присваивание
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    /**
     * @brief Добавление текстового сообщения в файл
     * @param message Сообщение для записи
     */
    void add(const std::string& message) override;

    /**
     * @brief Добавление фрейма с автоматическим форматированием времени
     * @param frame Уникальный указатель на объект фрейма
     */
    void add(std::unique_ptr<IFrame> frame) override;

    /**
     * @brief Гарантированная запись данных на диск
     */
    void commit() override;

private:
    /**
     * @brief Форматирование временной метки из double в hh:mm:ss
     * @param timestamp Временная метка в секундах
     * @return Отформатированная строка времени
     */
    std::string _formatTime(double timestamp) const;

    /**
     * @brief Безопасная запись в файл
     * @param content Данные для записи
     * @throws std::runtime_error При ошибке записи
     */
    void _writeToFile(const std::string& content);

    std::string filePath_;          ///< Путь к выходному файлу
    std::ofstream outputFile_;      ///< Поток вывода в файл
    mutable std::mutex writeMutex_; ///< Мьютекс для потокобезопасности
    bool needsCommit_ = false;      ///< Флаг необходимости сброса на диск
};