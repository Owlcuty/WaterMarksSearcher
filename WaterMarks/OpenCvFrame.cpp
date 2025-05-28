#include "OpenCvFrame.h"

OpenCvFrame::OpenCvFrame(cv::Mat frame, std::uint64_t time)
	: _frame(frame)
	, _time(time)
{

}

std::optional<cv::Mat> OpenCvFrame::getImpl() const
{
	return _frame;
}

std::uint64_t OpenCvFrame::getTime() const
{
	return _time;
}
