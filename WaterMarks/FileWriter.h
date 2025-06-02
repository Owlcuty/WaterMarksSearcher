#pragma once

#include "IWriter.h"

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
    /**
     * @brief ����������� � ��������� �����
     * @param filePath ���� � ��������� �����
     * @throws std::runtime_error ��� ������ �������� �����
     */
    explicit FileWriter(const std::string& filePath);

    /**
     * @brief ���������� � ��������� �����
     */
    ~FileWriter() override;

    // ������� ����������� � ������������
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    /**
     * @brief ���������� ���������� ��������� � ����
     * @param message ��������� ��� ������
     */
    void add(const std::string& message) override;

    /**
     * @brief ���������� ������ � �������������� ��������������� �������
     * @param frame ���������� ��������� �� ������ ������
     */
    void add(std::unique_ptr<IFrame> frame) override;

    /**
     * @brief ��������������� ������ ������ �� ����
     */
    void commit() override;

private:
    /**
     * @brief �������������� ��������� ����� �� double � hh:mm:ss
     * @param timestamp ��������� ����� � ��������
     * @return ����������������� ������ �������
     */
    std::string _formatTime(double timestamp) const;

    /**
     * @brief ���������� ������ � ����
     * @param content ������ ��� ������
     * @throws std::runtime_error ��� ������ ������
     */
    void _writeToFile(const std::string& content);

    std::string filePath_;          ///< ���� � ��������� �����
    std::ofstream outputFile_;      ///< ����� ������ � ����
    mutable std::mutex writeMutex_; ///< ������� ��� ������������������
    bool needsCommit_ = false;      ///< ���� ������������� ������ �� ����
};