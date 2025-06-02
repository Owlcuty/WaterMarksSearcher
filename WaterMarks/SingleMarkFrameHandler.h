#pragma once

#include "IFrameHandler.h"
#include "ILogger.h"

#include <optional>





#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

namespace
{
    class WatermarkDetector {
    public:
        WatermarkDetector(const std::string& modelPath);
        bool containsWatermark(const cv::Mat& frame, float threshold = 0.85f);

    private:
        cv::Mat _preprocessImage(const cv::Mat& img) const;

    private:
        cv::dnn::Net net;
        cv::Mat _watermark;
        const cv::Size inputSize{ 224, 224 };
        std::string inputName{ "input_1" };
        std::string outputName{ "dense_1" };
    };


    WatermarkDetector::WatermarkDetector(const std::string& modelPath) {
        net = cv::dnn::readNetFromONNX(
            modelPath + "\\model.onnx"
        );

        if (net.empty()) {
            throw std::runtime_error("Failed to load model");
        }
    }

    bool WatermarkDetector::containsWatermark(const cv::Mat& frame, float threshold) {
        cv::Mat input = _preprocessImage(frame);

        cv::Mat blob = cv::dnn::blobFromImage(
            input, 1.0, inputSize,
            cv::Scalar(0, 0, 0), true, false, CV_32F
        );

        net.setInput(blob, inputName);
        cv::Mat output = net.forward(outputName);

        float prob = output.at<float>(0);
        if (prob > threshold)
        {
            cv::imwrite(std::string("D:\\tmpFrames\\freame_") + std::to_string(prob) + ".png", frame);
            std::cout << "Probability: " << prob << std::endl;
        }

        return prob > threshold;

    }

    cv::Mat WatermarkDetector::_preprocessImage(const cv::Mat& img) const {
        cv::Mat resized;
        cv::resize(img, resized, inputSize);
        resized.convertTo(resized, CV_32F, 1.0 / 255.0);
        return resized;
    }
}




template <typename FrameType>
class SingleMarkFrameHandler : public IFrameHandler
{
public:
    SingleMarkFrameHandler() = default;
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger)
        : _logger(logger)
    {

    }
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger, std::shared_ptr<IFrame> waterMark)
        : _logger(logger)
    {

    }
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger, std::shared_ptr<WatermarkDetector> detector)
        : _logger(logger)
        , _detector(detector)
    {

    }

    bool handle() override
    {
        _log(LogLevel::Info, "HANDLE FRAME TYPE, DEFAULT FUNCTION");
        return false;
    }

    void setFrame(std::unique_ptr<IFrame> frame) override
    {
        _frame = std::move(frame);
    }

private:
    bool _isValid() const
    {
        return (_frame != nullptr);
    }
    void _log(LogLevel level, const std::string& message)
    {
        if (!_logger)
        {
            return;
        }
        _logger->log(level, message);
    }

private:
    std::unique_ptr<IFrame> _frame;
    std::shared_ptr<ILogger> _logger{};
    std::shared_ptr<WatermarkDetector> _detector{};
};

// ---------------------------------------- OPENCV --------------------------------------------


#include "OpenCvFrame.h"
#include <opencv2/opencv.hpp>
#include "Profiler.hpp"


template <>
class SingleMarkFrameHandler<OpenCvFrame> : public IFrameHandler
{
public:
    SingleMarkFrameHandler() = default;
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger)
        : _logger(logger)
    {

    }
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger, std::shared_ptr<WatermarkDetector> detector)
        : _logger(logger)
        , _detector(detector)
    {

    }

    bool handle() override
    {
        //PROFILE_SCOPE("HANDLE");
        if (!_isValid())
        {
            throw std::invalid_argument("Not valid");
        }

        cv::Mat frame = _frame->get<OpenCvFrame>().value();
        return _detector->containsWatermark(frame);

        return false;
        if (_hasTemplate)
        {
            return _matchTemplate();
        }

        return false;

    }

    void setFrame(std::unique_ptr<IFrame> frame) override
    {
        _frame = std::move(frame);

        std::string channelsFrame = "Frame has " + std::to_string(_frame->get<OpenCvFrame>()->channels());
        _log(LogLevel::Debug2, channelsFrame);
    }

private:
    bool _isValid() const
    {
        return (_frame != nullptr);
    }
    void _log(LogLevel level, const std::string& message)
    {
        if (!_logger)
        {
            return;
        }
        _logger->log(level, message);
    }

    cv::Mat _prepare(const cv::Mat& frame)
    {
        // -------------------- PREPARE --------------------
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
        clahe->apply(gray, gray);

        return gray;
        // --------------------------------------------------
    }

    bool _matchTemplate()
    {
        //PROFILE_START("Optional get cv::Mat");
        std::optional<cv::Mat> source = _frame->get<OpenCvFrame>();
        if (!source || !source.has_value())
        {
            _log(LogLevel::Warning, "Doesn't have source");
            return false;
        }
        //PROFILE_END();
        //PROFILE_START("Mat & name");
        auto& gray = source.value();// _prepare(source.value());
        //PROFILE_END();

        //PROFILE_START("Resize");
        cv::Mat img_small, templ_small;
        cv::resize(gray, img_small, cv::Size(), 0.2, 0.2, cv::INTER_LINEAR);
        cv::resize(_waterMark, templ_small, cv::Size(), 0.2, 0.2, cv::INTER_LINEAR);

        //PROFILE_END();

        // -------------- Check template --------------------

        //PROFILE_START("Match tample");
        cv::Mat result;
        cv::matchTemplate(img_small, templ_small, result, cv::TM_CCOEFF_NORMED);
        //PROFILE_END();


        //PROFILE_START("minMaxLoc + rectangle");
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
        maxLoc *= 5;
        
        bool show = false;
        if (maxVal > 0.7) {  // Порог можно настроить
            show = true;
            _log(LogLevel::Debug2, std::string("Original size: ") + std::to_string(gray.size().height) + "x" + std::to_string(gray.size().width));
            _log(LogLevel::Debug2, std::string("Small size: ") + std::to_string(img_small.size().height) + "x" + std::to_string(img_small.size().width));
        }
        else {
            _log(LogLevel::Debug16, "WaterMark is not found!");
        }
        //PROFILE_END();

        //PROFILE_START("Show log");
        if (show)
        {
            double time = _frame->getTime();
            std::string msg = "Time of watermark: " + std::to_string(time);
            _logger->log(LogLevel::Info, msg);
        }
        //PROFILE_END();
        return true;
    }

private:
    std::unique_ptr<IFrame> _frame;

    bool _hasTemplate {false};
    cv::Mat _waterMark;

    std::shared_ptr<ILogger> _logger {};


    std::string _pathModel {"D:\\projects\\model"};
    cv::dnn::Net _net;
    cv::Size _inputSize {cv::Size(128, 128)};

    std::shared_ptr<WatermarkDetector> _detector {};
};
