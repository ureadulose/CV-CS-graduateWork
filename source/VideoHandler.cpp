#include "general/VideoHandler.h"

VideoHandler::VideoHandler(const std::string& filename)
{
	_cap = new cv::VideoCapture(filename);
}

VideoHandler::~VideoHandler()
{
	delete _cap;
}

bool VideoHandler::ReadFrame()
{
	return _cap->read(_curr_rgb_frame);
}

cv::Mat VideoHandler::GetCurrRgbFrame()
{
	return _curr_rgb_frame;
}
