#include "general/CvFrameBufferHandler.h"

CvFrameBufferHandler::CvFrameBufferHandler(const std::string& filename)
{
	_cap = new cv::VideoCapture(filename);
	if (!_cap->isOpened())
	{
		std::cerr << "Error: Could not open video file " << filename << std::endl;
        return;
	}
	_cap->read(_curr_rgb_frame);
}

CvFrameBufferHandler::~CvFrameBufferHandler()
{
    delete _cap;
}

bool CvFrameBufferHandler::Exists()
{
    return _cap->isOpened();
}

bool CvFrameBufferHandler::ReadFrame()
{
    _prev_rgb_frame = _curr_rgb_frame.clone();
	return _cap->read(_curr_rgb_frame);
}

cv::Mat* CvFrameBufferHandler::GetCurrRgbFrame()
{
    return &_curr_rgb_frame;
}

cv::Mat* CvFrameBufferHandler::GetPrevRgbFrame()
{
    return &_prev_rgb_frame;
}

int CvFrameBufferHandler::GetFramerate()
{
    return _cap->get(cv::CAP_PROP_FPS);
}
