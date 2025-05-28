#include "SingleMarkFrameHandler.h"

#include <opencv2/opencv.hpp>


template <>
void SingleMarkFrameHandler<OpenCvFrame>::handle()
{
	if (!_isValid())
	{
		return;
	}

	cv::Mat gray;
	std::optional<cv::Mat> source = _frame->get<OpenCvFrame>();
	if (!source || source.has_value())
	{
		return;
	}
	cv::cvtColor(source.value(), gray, cv::COLOR_BGR2GRAY);

	while (1)
	{
		cv::imshow("FRAME MINEEEE", gray);

		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}
}
