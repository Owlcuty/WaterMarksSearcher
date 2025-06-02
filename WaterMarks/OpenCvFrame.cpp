#include "OpenCvFrame.h"

OpenCvFrame::OpenCvFrame(cv::Mat frame, double time)
	: _frame(frame)
	, _time(time)
{

}

OpenCvFrame::OpenCvFrame(std::string filepath)
{
	_frame = cv::imread(filepath);
}

std::optional<cv::Mat> OpenCvFrame::getImpl() const
{
	return _frame;
}

double OpenCvFrame::getTime() const
{
	return _time;
}
