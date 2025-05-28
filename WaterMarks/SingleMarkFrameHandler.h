#pragma once

#include "IFrameHandler.h"
#include "OpenCvFrame.h"
#include "ILogger.h"

#include <opencv2/opencv.hpp>

#include <optional>


template <typename FrameType>
class SingleMarkFrameHandler : public IFrameHandler
{
public:
    SingleMarkFrameHandler() = default;
    SingleMarkFrameHandler(std::shared_ptr<ILogger> logger);
    void handle() override;

    void init(std::unique_ptr<IFrame> frame) override
    {
        _frame = std::move(frame);
    }

private:
    bool _isValid() const
    {
        return (_frame != nullptr);
    }
    void _log(ILogger::LogLevel level, const std::string& message);

private:
    std::unique_ptr<IFrame> _frame;
    std::shared_ptr<ILogger> _logger {};
};
