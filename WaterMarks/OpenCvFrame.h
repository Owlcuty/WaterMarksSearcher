#pragma once

#include "IFrame.h"

#include <opencv2/opencv.hpp>


class OpenCvFrame : public IFrame
{
public:
	OpenCvFrame(cv::Mat frame, std::uint64_t time);
	~OpenCvFrame() = default;

	std::optional<cv::Mat> getImpl() const;

	std::uint64_t getTime() const override;

private:
	cv::Mat _frame;
	std::uint64_t _time;
};