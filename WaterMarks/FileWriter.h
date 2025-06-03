#pragma once

#include "IWriter.h"
#include "ILogger.h"

#include <fstream>
#include <mutex>
#include <string>

/**
 * @brief ���������� ���������� IWriter ��� ������ ������ � ����
 *
 * ����� ������������:
 * - ���������������� ������ ����� std::mutex
 * - �������������� ��������� ����� �� IFrame
 * - �������������� �������� ����������
 * - ��������������� ������ ����� commit()
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

    std::string filePath_;          ///< ���� � ��������� �����
    std::ofstream outputFile_;      ///< ����� ������ � ����
    mutable std::mutex writeMutex_; ///< ������� ��� ������������������
    bool needsCommit_ = false;      ///< ���� ������������� ������ �� ����
};
