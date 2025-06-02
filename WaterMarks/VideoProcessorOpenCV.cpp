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

#include "Profiler.hpp"

std::unique_ptr<IFrame> VideoProcessorOpenCV::getFrame()
{
	//PROFILE_START("CAP READ");
	cv::Mat cvframe;
	if (!_cap.read(cvframe))
	{
		_log(LogLevel::Debug, "Can't read anymore");
		//PROFILE_END();
		return {};
	}
	//PROFILE_END();

	//PROFILE_START("Get data and make_unique frame");
	double timestamp_ms = _cap.get(cv::CAP_PROP_POS_MSEC);
	std::unique_ptr<IFrame> frame = std::make_unique<OpenCvFrame>(cvframe, timestamp_ms / 1000.0);
	//PROFILE_END();

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

void VideoProcessorOpenCV::skipFrames(std::uint32_t frameSkip)
{
	//PROFILE_SCOPE("Skip Frames");
	cv::Mat trashFrame;
	for (std::uint32_t i = 0; i < frameSkip; i++)
	{
		_cap >> trashFrame;
	}
}

bool VideoProcessorOpenCV::_openMedia()
{
	_cap.open(_path);
	if (!_cap.isOpened())  // isOpened() returns true if capturing has been initialized.
	{
		_log(LogLevel::Error, "Cannot open the video file. \n");
		return false;
	}
	_log(LogLevel::Info, "Openned video file");
	return true;
}

void VideoProcessorOpenCV::_log(LogLevel level, const std::string& message)
{
	if (!_logger)
	{
		return;
	}
	_logger->log(level, message);
}