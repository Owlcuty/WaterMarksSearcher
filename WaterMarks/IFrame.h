#pragma once

#include <cstdint>
#include <optional>


class IFrame
{
public:
	IFrame() = default;
	virtual ~IFrame() = default;

	template <typename FrameType>
	auto get() const
	{
		return static_cast<const FrameType*>(this)->getImpl();
	}

	virtual double getTime() const = 0;
};
