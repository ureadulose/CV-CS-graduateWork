#include "general/VideoHandler.h"

VideoHandler::VideoHandler(const std::string& filename)
{
	_cap = new cv::VideoCapture(filename);
	if (!_cap->isOpened())
	{
		std::cerr << "Error: Could not open video file " << filename << std::endl;
        return;
	}
	_cap->read(_curr_rgb_frame);
}

VideoHandler::~VideoHandler()
{
	delete _cap;
}

bool VideoHandler::ReadFrame()
{
	_prev_rgb_frame = _curr_rgb_frame.clone();
	return _cap->read(_curr_rgb_frame);
}

cv::Mat* VideoHandler::GetCurrRgbFrame()
{
	return &_curr_rgb_frame;
}

cv::Mat* VideoHandler::GetPrevRgbFrame()
{
	return &_prev_rgb_frame;
}
