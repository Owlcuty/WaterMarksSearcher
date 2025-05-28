#include "VideoProcessorOpenCV.h"

#include <opencv2/opencv.hpp>


VideoProcessorOpenCV::VideoProcessorOpenCV(std::shared_ptr<ILogger> logger)
	: _logger(logger)
{

}

VideoProcessorOpenCV::~VideoProcessorOpenCV()
{

}

void VideoProcessorOpenCV::init(const std::string& videoPath)
{
	_path = videoPath;
	_openMedia();
}

std::queue<IFrame> VideoProcessorOpenCV::getFrames(std::uint32_t number)
{
	return {};
}

std::uint64_t VideoProcessorOpenCV::getPosition() const
{
	return _position;
}

void VideoProcessorOpenCV::setPosition(std::uint64_t framePosition)
{
	_position = framePosition;
}

bool VideoProcessorOpenCV::_openMedia()
{
	cv::VideoCapture cap(_path);
	if (!cap.isOpened())  // isOpened() returns true if capturing has been initialized.
	{
		_log(ILogger::LogLevel::Error, "Cannot open the video file. \n");
		return false;
	}
	return true;
}

void VideoProcessorOpenCV::_log(ILogger::LogLevel level, const std::string& message)
{
	if (!_logger)
	{
		return;
	}
	_logger->log(level, message);
}