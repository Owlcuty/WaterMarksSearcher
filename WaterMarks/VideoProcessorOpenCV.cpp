#include "VideoProcessorOpenCV.h"
#include "OpenCvFrame.h"

#include <opencv2/highgui/highgui.hpp>


VideoProcessorOpenCV::VideoProcessorOpenCV(std::shared_ptr<ILogger> logger)
	: _logger(logger)
{

}

VideoProcessorOpenCV::~VideoProcessorOpenCV()
{
	_cap.release();
}

void VideoProcessorOpenCV::init(const std::string& videoPath)
{
	_path = videoPath;
	_openMedia();
}

std::unique_ptr<IFrame> VideoProcessorOpenCV::getFrame()
{
	cv::Mat cvframe;
	if (!_cap.read(cvframe))
	{
		_log(ILogger::LogLevel::Debug, "Can't read anymore");
		return {};
	}

	std::unique_ptr<IFrame> frame = std::make_unique<OpenCvFrame>(cvframe, 0);

	return frame;
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
	_cap.open(_path);
	if (!_cap.isOpened())  // isOpened() returns true if capturing has been initialized.
	{
		_log(ILogger::LogLevel::Error, "Cannot open the video file. \n");
		return false;
	}
	_log(ILogger::LogLevel::Info, "Openned video file");
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