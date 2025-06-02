#pragma once

#include "IFrame.h"

#include <opencv2/opencv.hpp>


class OpenCvFrame : public IFrame
{
public:
	OpenCvFrame(cv::Mat frame, double time);
	OpenCvFrame(std::string filepath);
	~OpenCvFrame() = default;

	std::optional<cv::Mat> getImpl() const;

	double getTime() const override;

private:
	cv::Mat _frame;
	double _time {0};
};